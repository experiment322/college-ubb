create database TEST
go

use TEST

create table MATERIAL
(
  ID       int           not null,
  DENUMIRE nvarchar(256) not null,
  constraint MATERIAL_PK_ID primary key (ID),
  constraint MATERIAL_UQ_DENUMIRE unique (DENUMIRE),
)
go

create table VESTA
(
  ID          int            not null,
  MODEL       nvarchar(256)  not null,
  PRET        int            not null,
  DESCRIERE   nvarchar(1024) not null,
  MATERIAL_ID int            not null,
  constraint VESTA_PK_ID primary key (ID),
  constraint VESTA_UQ_MODEL unique (MODEL),
  constraint VESTA_FK_MATERIAL foreign key (MATERIAL_ID) references MATERIAL (ID),
)
go

create table RASA
(
  ID        int            not null,
  NUME      nvarchar(256)  not null,
  DESCRIERE nvarchar(1024) not null,
  ORIGINE   nvarchar(256)  not null,
  ISTORIC   nvarchar(1024) not null,
  constraint RASA_PK_ID primary key (ID),
  constraint RASA_UQ_NUME unique (NUME),
)
go

create table CAINE
(
  ID           int           not null,
  NUME         nvarchar(256) not null,
  DATA_NASTERE date          not null,
  RASA_ID      int           not null,
  constraint CAINE_PK_ID primary key (ID),
  constraint CAINE_UQ_NUME unique (NUME),
  constraint CAINE_FK_RASA foreign key (RASA_ID) references RASA (ID),
)
go

create table VESTA_CAINE
(
  VESTA_ID  int not null,
  CAINE_ID  int not null,
  CANTITATE int not null,
  constraint VESTA_CAINE_PK_VESTA_ID_CAINE_ID primary key (VESTA_ID, CAINE_ID),
  constraint VESTA_CAINE_FK_VESTA foreign key (VESTA_ID) references VESTA (ID),
  constraint VESTA_CAINE_FK_CAINE foreign key (CAINE_ID) references CAINE (ID),
)
go

create proc uspCumparaVestaCaine @IdVesta int, @IdCaine int, @Cantitate int
as
begin
  if exists(select * from VESTA_CAINE where VESTA_ID = @IdVesta and CAINE_ID = @IdCaine)
    begin
      update VESTA_CAINE set CANTITATE = @Cantitate where VESTA_ID = @IdVesta and CAINE_ID = @IdCaine
    end
  else
    begin
      insert into VESTA_CAINE values (@IdVesta, @IdCaine, @Cantitate)
    end
end
go

create view ACHIZITII_OGARI_DE_IBIZA as
select M.DENUMIRE   as MATERIAL_VESTA,
       V.MODEL      as MODEL_VESTA,
       VC.CANTITATE as CANTIATE,
       C.NUME       as NUME_CAINE,
       R.NUME       as RASA
from VESTA_CAINE VC
       join VESTA V on VC.VESTA_ID = V.ID
       join CAINE C on VC.CAINE_ID = C.ID
       join MATERIAL M on V.MATERIAL_ID = M.ID
       join RASA R on C.RASA_ID = R.ID
where R.NUME = 'Ogar de Ibiza';


-- executions
insert into MATERIAL
values (1, 'poliester'),
       (2, 'bumbac'),
       (3, 'matase');

insert into VESTA
values (1, 'urban camo', 100, 'descriere urban camo', 2),
       (2, 'clasic', 75, 'descriere clasic', 1),
       (3, 'vesta iarna', 130, 'descriere vesta iarna', 2),
       (4, 'vesta fancy', 200, 'descriere vesta fancy', 3);

insert into RASA
values (1, 'Ogar de Ibiza', 'descriere ogar de ibiza', 'Ibiza', 'istoric ogar de ibiza'),
       (2, 'Ciobanesc Carpatin', 'descriere ciobanesc carpatin', 'Germania', 'istoric ciobanesc carpatin'),
       (3, 'Chihuahua', 'descriere chihuahua', 'Mexic', 'istoric chihuahua');

insert into CAINE
values (1, 'Rex', datefromparts(2008, 10, 10), 2),
       (2, 'Miki', datefromparts(2012, 8, 6), 3),
       (3, 'Otto', datefromparts(2005, 12, 9), 1),
       (4, 'Mira', datefromparts(2007, 7, 24), 1);

exec uspCumparaVestaCaine 3, 2, 7;
exec uspCumparaVestaCaine 4, 2, 3;
exec uspCumparaVestaCaine 1, 1, 10;
exec uspCumparaVestaCaine 1, 3, 5;
exec uspCumparaVestaCaine 2, 4, 12;

select * from VESTA_CAINE

exec uspCumparaVestaCaine 2, 3, 40

select * from ACHIZITII_OGARI_DE_IBIZA
