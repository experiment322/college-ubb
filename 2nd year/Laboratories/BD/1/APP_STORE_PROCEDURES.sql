use APP_STORE
go

create table DB_VERSION
(
  ID                    int            not null identity primary key,
  SQL_OPERATION         nvarchar(4000) not null,
  REVERSE_SQL_OPERATION nvarchar(4000) not null
)
go

set identity_insert DB_VERSION on
insert into DB_VERSION (ID, SQL_OPERATION, REVERSE_SQL_OPERATION)
values (0, '', '')
set identity_insert DB_VERSION off
go

create proc uspChangeColumnType @ColumnName nvarchar(250),
                                @ColumnType nvarchar(250),
                                @TableName nvarchar(250),
                                @SQL_OUT nvarchar(4000) = null out
as
begin
  declare @SQL_OPERATION nvarchar(4000) =
      'alter table ' + quotename(@TableName) + ' alter column ' + quotename(@ColumnName) + ' ' + quotename(@ColumnType)
  if @SQL_OUT is not null
    set @SQL_OUT = @SQL_OPERATION
  else
    begin
      declare @OldColumnType nvarchar(250) = (select type_name(system_type_id)
                                              from sys.columns
                                              where name = @ColumnName
                                                and object_id = object_id(@TableName))
      begin try
        exec sp_executesql @SQL_OPERATION
      end try
      begin catch
        throw
      end catch
      declare @REVERSE_SQL_OPERATION nvarchar(4000) = ''
      exec uspChangeColumnType @ColumnName, @OldColumnType, @TableName, @REVERSE_SQL_OPERATION out
      insert into DB_VERSION values (@SQL_OPERATION, @REVERSE_SQL_OPERATION)
    end
end
go

create proc uspSetColumnDefaultValue @ColumnName nvarchar(250),
                                     @DefaultValue nvarchar(250),
                                     @TableName nvarchar(250),
                                     @SQL_OUT nvarchar(4000) = null out
as
begin
  declare @SQL_OPERATION nvarchar(4000) =
      'alter table ' + quotename(@TableName) + ' add constraint ' + quotename(@ColumnName + '_default_value') + ' ' +
      'default ' + quotename(@DefaultValue, '''') + ' for ' + quotename(@ColumnName)
  if @SQL_OUT is not null
    set @SQL_OUT = @SQL_OPERATION
  else
    begin
      begin try
        exec sp_executesql @SQL_OPERATION
      end try
      begin catch
        throw
      end catch
      declare @REVERSE_SQL_OPERATION nvarchar(4000) = ''
      exec uspUnsetColumnDefaultValue @ColumnName, @TableName, @REVERSE_SQL_OPERATION out
      insert into DB_VERSION values (@SQL_OPERATION, @REVERSE_SQL_OPERATION)
    end
end
go

create proc uspUnsetColumnDefaultValue @ColumnName nvarchar(250),
                                       @TableName nvarchar(250),
                                       @SQL_OUT nvarchar(4000) = null out
as
begin
  declare @SQL_OPERATION nvarchar(4000) =
      'alter table ' + quotename(@TableName) + ' drop constraint ' + quotename(@ColumnName + '_default_value')
  if @SQL_OUT is not null
    set @SQL_OUT = @SQL_OPERATION
  else
    begin
      declare @DefaultValue nvarchar(250) = (select substring(definition, 3, len(definition) - 4)
                                             from sys.default_constraints
                                             where parent_column_id =
                                                   columnproperty(object_id(@TableName), @ColumnName, 'ColumnId'))
      begin try
        exec sp_executesql @SQL_OPERATION
      end try
      begin catch
        throw
      end catch
      declare @REVERSE_SQL_OPERATION nvarchar(4000) = ''
      exec uspSetColumnDefaultValue @ColumnName, @DefaultValue, @TableName, @REVERSE_SQL_OPERATION out
      insert into DB_VERSION values (@SQL_OPERATION, @REVERSE_SQL_OPERATION)
    end
end
go

create proc uspCreateTable @TableName nvarchar(250),
                           @SQL_OUT nvarchar(4000) = null out
as
begin
  declare @SQL_OPERATION nvarchar(4000) =
    'create table ' + quotename(@TableName) + ' (ID int primary key)'
  if @SQL_OUT is not null
    set @SQL_OUT = @SQL_OPERATION
  else
    begin
      begin try
        exec sp_executesql @SQL_OPERATION
      end try
      begin catch
        throw
      end catch
      declare @REVERSE_SQL_OPERATION nvarchar(4000) = ''
      exec uspDropTable @TableName, @REVERSE_SQL_OPERATION out
      insert into DB_VERSION values (@SQL_OPERATION, @REVERSE_SQL_OPERATION)
    end
end
go

create proc uspDropTable @TableName nvarchar(250),
                         @SQL_OUT nvarchar(4000) = null out
as
begin
  declare @SQL_OPERATION nvarchar(4000) =
    'drop table ' + quotename(@TableName)
  if @SQL_OUT is not null
    set @SQL_OUT = @SQL_OPERATION
  else
    begin
      begin try
        exec sp_executesql @SQL_OPERATION
      end try
      begin catch
        throw
      end catch
      declare @REVERSE_SQL_OPERATION nvarchar(4000) = ''
      exec uspCreateTable @TableName, @REVERSE_SQL_OPERATION out
      insert into DB_VERSION values (@SQL_OPERATION, @REVERSE_SQL_OPERATION)
    end
end
go

create proc uspAddColumn @ColumnName nvarchar(250),
                         @ColumnType nvarchar(250),
                         @TableName nvarchar(250),
                         @SQL_OUT nvarchar(4000) = null out
as
begin
  declare @SQL_OPERATION nvarchar(4000) =
      'alter table ' + quotename(@TableName) + ' add ' + quotename(@ColumnName) + ' ' + quotename(@ColumnType)
  if @SQL_OUT is not null
    set @SQL_OUT = @SQL_OPERATION
  else
    begin
      begin try
        exec sp_executesql @SQL_OPERATION
      end try
      begin catch
        throw
      end catch
      declare @REVERSE_SQL_OPERATION nvarchar(4000) = ''
      exec uspDropColumn @ColumnName, @TableName, @REVERSE_SQL_OPERATION out
      insert into DB_VERSION values (@SQL_OPERATION, @REVERSE_SQL_OPERATION)
    end
end
go

create proc uspDropColumn @ColumnName nvarchar(250),
                          @TableName nvarchar(250),
                          @SQL_OUT nvarchar(4000) = null out
as
begin
  declare @SQL_OPERATION nvarchar(4000) =
      'alter table ' + quotename(@TableName) + ' drop column ' + quotename(@ColumnName)
  if @SQL_OUT is not null
    set @SQL_OUT = @SQL_OPERATION
  else
    begin
      declare @ColumnType nvarchar(250) = (select type_name(system_type_id)
                                           from sys.columns
                                           where name = @ColumnName
                                             and object_id = object_id(@TableName))
      begin try
        exec sp_executesql @SQL_OPERATION
      end try
      begin catch
        throw
      end catch
      declare @REVERSE_SQL_OPERATION nvarchar(4000) = ''
      exec uspAddColumn @ColumnName, @ColumnType, @TableName, @REVERSE_SQL_OPERATION out
      insert into DB_VERSION values (@SQL_OPERATION, @REVERSE_SQL_OPERATION)
    end
end
go

create proc uspAddForeignKey @ColumnName nvarchar(250),
                             @TableName nvarchar(250),
                             @ForeignColumnName nvarchar(250),
                             @ForeignTableName nvarchar(250),
                             @SQL_OUT nvarchar(4000) = null out
as
begin
  declare @SQL_OPERATION nvarchar(4000) =
      'alter table ' + quotename(@TableName) + ' add constraint ' + quotename(@ColumnName + '_foreign_key') + ' ' +
      'foreign key (' + quotename(@ColumnName) + ') references ' +
      quotename(@ForeignTableName) + '(' + quotename(@ForeignColumnName) + ')'
  if @SQL_OUT is not null
    set @SQL_OUT = @SQL_OPERATION
  else
    begin
      begin try
        exec sp_executesql @SQL_OPERATION
      end try
      begin catch
        throw
      end catch
      declare @REVERSE_SQL_OPERATION nvarchar(4000) = ''
      exec uspDropForeignKey @ColumnName, @TableName, @REVERSE_SQL_OPERATION out
      insert into DB_VERSION values (@SQL_OPERATION, @REVERSE_SQL_OPERATION)
    end
end
go

create proc uspDropForeignKey @ColumnName nvarchar(250),
                              @TableName nvarchar(250),
                              @SQL_OUT nvarchar(4000) = null out
as
begin
  declare @SQL_OPERATION nvarchar(4000) =
      'alter table ' + quotename(@TableName) + ' drop constraint ' + quotename(@ColumnName + '_foreign_key')
  if @SQL_OUT is not null
    set @SQL_OUT = @SQL_OPERATION
  else
    begin
      declare @ForeignTableName nvarchar(250) = object_name((select referenced_object_id
                                                             from sys.foreign_key_columns
                                                             where parent_object_id = object_id(@TableName)
                                                               and parent_column_id =
                                                                   columnproperty(object_id(@TableName), @ColumnName, 'ColumnId')))
      declare @ForeignColumnName nvarchar(250) = col_name(object_id(@ForeignTableName),
                                                          (select referenced_column_id
                                                           from sys.foreign_key_columns
                                                           where parent_object_id = object_id(@TableName)
                                                             and parent_column_id =
                                                                 columnproperty(object_id(@TableName), @ColumnName, 'ColumnId')))
      begin try
        exec sp_executesql @SQL_OPERATION
      end try
      begin catch
        throw
      end catch
      declare @REVERSE_SQL_OPERATION nvarchar(4000) = ''
      exec uspAddForeignKey @ColumnName, @TableName, @ForeignColumnName, @ForeignTableName, @REVERSE_SQL_OPERATION out
      insert into DB_VERSION values (@SQL_OPERATION, @REVERSE_SQL_OPERATION)
    end
end
go

create proc uspSetDbVersion @Version int
as
begin
  declare @LatestVersion int = (select max(ID) from DB_VERSION)
  declare @TargetVersion int = (select ID from DB_VERSION where ID = @Version)
  if @TargetVersion is null
    throw 51000, 'The version does not exist.', 1
  while @LatestVersion > @TargetVersion
  begin
    declare @REVERSE_SQL_OPERATION nvarchar(4000) = (select REVERSE_SQL_OPERATION from DB_VERSION where ID = @LatestVersion)
    delete from DB_VERSION where ID = @LatestVersion
    exec sp_executesql @REVERSE_SQL_OPERATION
    set @LatestVersion = @LatestVersion - 1
  end
end
go


-- static versions
create proc uspSetDbVersion1
as
exec uspCreateTable 'TEST'
go

create proc uspSetDbVersion2
as
exec uspAddColumn 'COL', 'bigint', 'TEST'
go

create proc uspSetDbVersion3
as
exec uspChangeColumnType 'COL', 'int', 'TEST'
go

create proc uspSetDbVersion4
as
exec uspSetColumnDefaultValue 'COL', '777', 'TEST'
go

create proc uspSetDbVersion5
as
exec uspAddForeignKey 'COL', 'TEST', 'ID', 'APP'
go

create proc uspSetDbPredefinedVersion @Version int
as
begin
  if @Version < 0 or @Version > 5
    begin
      throw 51000, 'Please select a version between 0 - 5.', 1
    end
  declare @LatestVersion int = (select max(ID)
                                from (select row_number() over (order by ID) - 1 as 'ID'
                                      from DB_VERSION) as VERSION)
  if @Version > @LatestVersion
    begin
      while @LatestVersion < @Version
      begin
        if @LatestVersion = 0
          exec uspSetDbVersion1
        if @LatestVersion = 1
          exec uspSetDbVersion2
        if @LatestVersion = 2
          exec uspSetDbVersion3
        if @LatestVersion = 3
          exec uspSetDbVersion4
        if @LatestVersion = 4
          exec uspSetDbVersion5
        set @LatestVersion = @LatestVersion + 1
      end
    end
  else
    begin
      set @Version = (select ID
                      from (select row_number() over (order by ID) - 1 as 'ROW_NUMBER', *
                            from DB_VERSION) as VERSION
                      where ROW_NUMBER = @Version)
      exec uspSetDbVersion @Version
    end
end
go
