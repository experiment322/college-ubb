create database APP_STORE
go

use APP_STORE
go

create table COMPANY
(
  ID      int          not null
    primary key,
  NAME    varchar(255) not null
    unique,
  CONTACT varchar(255) not null
)
go

create table APP_CATEGORY
(
  ID   int          not null
    primary key,
  NAME varchar(255) not null
    unique
)
go

create table APP
(
  ID              int          not null
    primary key,
  NAME            varchar(255) not null
    unique,
  PRICE           int          not null,
  COMPANY_ID      int          not null
    references COMPANY,
  APP_CATEGORY_ID int          not null
    references APP_CATEGORY
)
go

create table APP_VER
(
  ID      int          not null
    primary key,
  SRC     varchar(255) not null,
  VERSION varchar(255) not null,
  APP_ID  int          not null
    references APP,
  constraint UNIQUE_APP_VERSION
    unique (VERSION, APP_ID)
)
go

create table MEMBER
(
  ID         int          not null
    primary key,
  NAME       varchar(255) not null
    unique,
  COMPANY_ID int
    references COMPANY
)
go

create table FOLLOWED_MEMBER
(
  ID                  int not null
    primary key,
  FOLLOWED_MEMBER_ID  int not null
    references MEMBER,
  FOLLOWING_MEMBER_ID int not null
    references MEMBER,
  constraint UNIQUE_FOLLOWER_FOLLOWED
    unique (FOLLOWED_MEMBER_ID, FOLLOWING_MEMBER_ID)
)
go

create table COMPANY_REVIEW
(
  ID         int          not null
    primary key,
  MSG        varchar(255) not null,
  DATE       datetime     not null,
  MEMBER_ID  int          not null
    references MEMBER,
  COMPANY_ID int          not null
    references COMPANY,
  constraint UNIQUE_MEMBER_COMPANY_REVIEW
    unique (MEMBER_ID, COMPANY_ID)
)
go

create table APP_REVIEW
(
  ID         int          not null
    primary key,
  MSG        varchar(255) not null,
  DATE       datetime     not null,
  MEMBER_ID  int          not null
    references MEMBER,
  APP_VER_ID int          not null
    references APP_VER,
  constraint UNIQUE_MEMBER_APP_VER_REVIEW
    unique (MEMBER_ID, APP_VER_ID)
)
go

create table MEMBER_APP_INSTALLED
(
  ID         int not null
    primary key,
  MEMBER_ID  int not null
    references MEMBER,
  APP_VER_ID int not null
    references APP_VER,
  constraint UNIQUE_MEMBER_APP_INSTALLED
    unique (MEMBER_ID, APP_VER_ID)
)
go

create table MEMBER_APP_PURCHASED
(
  ID        int      not null
    primary key,
  MEMBER_ID int      not null
    references MEMBER,
  APP_ID    int      not null
    references APP,
  DATE      datetime not null,
  constraint UNIQUE_MEMBER_APP_PURCHASED
    unique (MEMBER_ID, APP_ID)
)
go
