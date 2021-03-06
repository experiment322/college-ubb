use APP_STORE
go

create view CHEAP_APP as
select ID, NAME, PRICE, COMPANY_ID, APP_CATEGORY_ID
from APP
where PRICE < 100
go

create view SOCIAL as
select FOLLOWER.ID as FOLLOWER_ID, FOLLOWER.NAME as FOLLOWER, FOLLOWED.ID as FOLLOWED_ID, FOLLOWED.NAME as FOLLOWED
from FOLLOWED_MEMBER
       join MEMBER FOLLOWER on FOLLOWED_MEMBER.FOLLOWING_MEMBER_ID = FOLLOWER.ID
       join MEMBER FOLLOWED on FOLLOWED_MEMBER.FOLLOWED_MEMBER_ID = FOLLOWED.ID
go

create view APP_CATEGORY_COUNT as
select APP_CATEGORY.ID,
       APP_CATEGORY.NAME,
       sum(case when APP.ID is null then 0 else 1 end) as APPS
from APP_CATEGORY
       left join APP APP on APP_CATEGORY.ID = APP.APP_CATEGORY_ID
group by APP_CATEGORY.ID, APP_CATEGORY.NAME
go
