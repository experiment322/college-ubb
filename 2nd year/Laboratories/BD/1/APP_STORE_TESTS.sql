use APP_STORE
go

-- TODO: change tables

insert into Tests
values ('delete'),
       ('insert'),
       ('select')
go

insert into Tables
values ('FOLLOWED_MEMBER'),
       ('APP_CATEGORY'),
       ('APP_VER')
go

insert into Views
values ('APP_CATEGORY_COUNT'),
       ('CHEAP_APP'),
       ('SOCIAL')
go

insert into TestTables
select Tests.TestID, Tables.TableID, 5000 as NoOfRows, row_number() over (order by Tables.TableID) as Position
from Tests,
     Tables
where Tests.Name = 'delete'
order by Tables.TableID
go

insert into TestTables
select Tests.TestID, Tables.TableID, 5000 as NoOfRows, row_number() over (order by Tables.TableID) as Position
from Tests,
     Tables
where Tests.Name = 'insert'
order by Tables.TableID
go

insert into TestViews
select Tests.TestID, Views.ViewID
from Tests,
     Views
where Tests.Name = 'select'
order by Views.ViewID
go

create proc uspTestInsertRow_APP_CATEGORY @Position int
as
begin
  insert into APP_CATEGORY values (@Position, 'TEST ' + cast(@Position as nvarchar(16)))
end
go

create proc uspTestInsertRow_APP_VER @Position int
as
begin
  declare @AppId int = (SELECT TOP 1 ID FROM APP ORDER BY NEWID())
  insert into APP_VER values (@Position, 'TEST', 'TEST ' + cast(@Position as nvarchar(16)), @AppId)
end
go

create proc uspTestInsertRow_FOLLOWED_MEMBER @Position int
as
begin
  insert into FOLLOWED_MEMBER
  select top 1 @Position, M1.ID, M2.ID
  from MEMBER M1,
       MEMBER M2
  where not exists(select FOLLOWED_MEMBER_ID, FOLLOWING_MEMBER_ID
                   from FOLLOWED_MEMBER
                   where FOLLOWED_MEMBER_ID = M1.ID
                     and FOLLOWING_MEMBER_ID = M2.ID)
end
go

create proc uspTestDeleteRow_APP_CATEGORY @Position int
as
begin
  delete from APP_CATEGORY where ID = @Position
end
go

create proc uspTestDeleteRow_APP_VER @Position int
as
begin
  delete from APP_VER where ID = @Position
end
go

create proc uspTestDeleteRow_FOLLOWED_MEMBER @Position int
as
begin
  delete from FOLLOWED_MEMBER where ID = @Position
end
go

create proc uspRunTests @Description nvarchar(2000)
as
begin
  set nocount on
  insert into TestRuns values (@Description, current_timestamp, null)
  declare @CurrentTestRun int = ident_current('TestRuns')

  -- Table delete testing
  declare @DeleteId int = (select TestID from Tests where Name = 'delete')
  declare DeleteCursor cursor local for select *
                                        from TestTables
                                        where TestID = @DeleteId
                                        order by Position
  declare @TestIdD int
  declare @TableIdD int
  declare @NoOfRowsD int
  declare @PositionD int

  open DeleteCursor
  fetch next from DeleteCursor into @TestIdD, @TableIdD, @NoOfRowsD, @PositionD
  while @@FETCH_STATUS = 0
  begin
    declare @RowIdD int = 0
    declare @TestedTableD nvarchar(50) = (select Name from Tables where TableID = @TableIdD)
    declare @DeleteStartAt timestamp = current_timestamp
    while @RowIdD < @NoOfRowsD
    begin
      declare @SqlRowDelete nvarchar(1024) = 'exec uspTestDeleteRow_' + @TestedTableD + ' ' +
                                             cast(@RowIdD as nvarchar(16))
      exec sp_executesql @SqlRowDelete
      set @RowIdD = @RowIdD + 1
    end
    insert into TestRunTables values (@CurrentTestRun, @TableIdD, @DeleteStartAt, current_timestamp)
    fetch next from DeleteCursor into @TestIdD, @TableIdD, @NoOfRowsD, @PositionD
  end
  close DeleteCursor
  deallocate DeleteCursor

  -- Table insert testing
  declare @InsertId int = (select TestID from Tests where Name = 'insert')
  declare InsertCursor cursor local for select *
                                        from TestTables
                                        where TestID = @InsertId
                                        order by Position desc
  declare @TestIdI int
  declare @TableIdI int
  declare @NoOfRowsI int
  declare @PositionI int

  open InsertCursor
  fetch next from InsertCursor into @TestIdI, @TableIdI, @NoOfRowsI, @PositionI
  while @@FETCH_STATUS = 0
  begin
    declare @RowIdI int = 0
    declare @TestedTableI nvarchar(50) = (select Name from Tables where TableID = @TableIdI)
    declare @InsertStartAt timestamp = current_timestamp
    while @RowIdI < @NoOfRowsI
    begin
      declare @SqlRowGenerate nvarchar(1024) = 'exec uspTestInsertRow_' + @TestedTableI + ' ' +
                                               cast(@RowIdI as nvarchar(16))
      exec sp_executesql @SqlRowGenerate
      set @RowIdI = @RowIdI + 1
    end
    insert into TestRunTables values (@CurrentTestRun, @TableIdI, @InsertStartAt, current_timestamp)
    fetch next from InsertCursor into @TestIdI, @TableIdI, @NoOfRowsI, @PositionI
  end
  close InsertCursor
  deallocate InsertCursor

  -- View testing
  declare @SelectId int = (select TestID from Tests where Name = 'select')
  declare TestViewsCursor cursor local for select *
                                           from TestViews
                                           where TestID = @SelectId
  declare @TestIdV int
  declare @ViewIdV int

  open TestViewsCursor
  fetch next from TestViewsCursor into @TestIdV, @ViewIdV
  while @@FETCH_STATUS = 0
  begin
    declare @TestedView nvarchar(50) = (select Name from Views where ViewID = @ViewIdV)
    declare @SelectStartAt datetime = current_timestamp
    declare @SqlSelect nvarchar(1024) = 'select * from ' + @TestedView
    exec sp_executesql @SqlSelect
    insert into TestRunViews values (@CurrentTestRun, @ViewIdV, @SelectStartAt, current_timestamp)
    fetch next from TestViewsCursor into @TestIdV, @ViewIdV
  end
  close TestViewsCursor
  deallocate TestViewsCursor

  -- Update end time for current test run
  update TestRuns set EndAt = current_timestamp where TestRunID = @CurrentTestRun;
  set nocount off
end
go
