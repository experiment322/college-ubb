use APP_STORE

-- returns the applications purchased by members being followed by the member with the given name
-- they are ordered by purchase count descending to show the most popular apps among the followed users
select APP.NAME                                                                                      as Application,
       string_agg(MEMBER2.NAME, ',')                                                                 as Buyers,
       len(string_agg(MEMBER2.NAME, ',')) - len(replace(string_agg(MEMBER2.NAME, ','), ',', '')) + 1 as Count
from MEMBER MEMBER1
       join FOLLOWED_MEMBER FOLLOWED_MEMBER on MEMBER1.ID = FOLLOWED_MEMBER.FOLLOWING_MEMBER_ID
       join MEMBER MEMBER2 on MEMBER2.ID = FOLLOWED_MEMBER.FOLLOWED_MEMBER_ID
       join MEMBER_APP_PURCHASED PURCHASE on PURCHASE.MEMBER_ID = MEMBER2.ID
       join APP APP on APP.ID = PURCHASE.APP_ID
where MEMBER1.NAME = 'gmcnirlanc3'
group by APP.NAME
order by Count desc, Application asc

-- returns the most purchased applications from the specified category in reverse order
-- can also be used to promote not so successful applications
select APP.NAME as Application, count(*) as Purchases
from APP
       join MEMBER_APP_PURCHASED PURCHASE on APP.ID = PURCHASE.APP_ID
       join APP_CATEGORY CATEGORY on APP.APP_CATEGORY_ID = CATEGORY.ID
where CATEGORY.NAME = 'Finance'
group by APP.NAME, CATEGORY.NAME
having count(*) >= 3
order by Purchases desc, Application asc

-- returns the number of employees for each company
select COMPANY.NAME as Company, count(*) as Employees
from COMPANY
       join MEMBER MEMBER on COMPANY.ID = MEMBER.COMPANY_ID
group by COMPANY.NAME
order by Company asc

-- returns application count for every application category
select APP_CATEGORY.NAME as Category, count(*) as Applications
from APP_CATEGORY
       join APP APP on APP_CATEGORY.ID = APP.APP_CATEGORY_ID
group by APP_CATEGORY.NAME
order by Category asc

-- returns all app and company reviews ordered by app/company name made by the member with the given name
-- ids can repeat because the results are from both APP_REVIEW and COMPANY_REVIEW
select *
from (select APP_REVIEW.ID                       as Id,
             'Application'                       as Type,
             concat(APP.NAME, ' V', VER.VERSION) as Target,
             MEMBER.NAME                         as Member,
             APP_REVIEW.MSG                      as Review
      from APP_REVIEW
             join MEMBER MEMBER on APP_REVIEW.MEMBER_ID = MEMBER.ID
             join APP_VER VER on APP_REVIEW.APP_VER_ID = VER.ID
             join APP APP on VER.APP_ID = APP.ID
      union
      select COMPANY_REVIEW.ID  as Id,
             'Company'          as Type,
             COMPANY.NAME       as Target,
             MEMBER.NAME        as Member,
             COMPANY_REVIEW.MSG as Review
      from COMPANY_REVIEW
             join MEMBER MEMBER on COMPANY_REVIEW.MEMBER_ID = MEMBER.ID
             join COMPANY COMPANY on COMPANY_REVIEW.COMPANY_ID = COMPANY.ID) as REVIEWS
where Member = 'dcranglc'
order by Type asc, Target asc

-- returns the most purchased app from every company
select COMPANY.NAME as Company, APP.NAME as Application, count(*) as Purchases
from APP
       join MEMBER_APP_PURCHASED PURCHASE on APP.ID = PURCHASE.APP_ID
       join COMPANY COMPANY on APP.COMPANY_ID = COMPANY.ID
GROUP BY COMPANY.NAME, APP.NAME
having count(*) >= 3
order by Purchases desc

-- returns a list of members being followed (can be used to suggest members to follow to new users?)
select distinct MEMBER.NAME as Member
from MEMBER MEMBER
       join FOLLOWED_MEMBER FOLLOWED_MEMBER on MEMBER.ID = FOLLOWED_MEMBER.FOLLOWED_MEMBER_ID
order by Member asc

-- returns members to follow based on common purchased apps (common interests?)
select OTHER_MEMBER.NAME as Suggested
from (select THIS_MEMBER.NAME as Member, THIS_MEMBER_APP_PURCHASED.APP_ID as Application
      from MEMBER THIS_MEMBER
             join MEMBER_APP_PURCHASED THIS_MEMBER_APP_PURCHASED on THIS_MEMBER.ID = THIS_MEMBER_APP_PURCHASED.MEMBER_ID
      where THIS_MEMBER.NAME = 'kskeen27') as THIS_MEMBER_APP
       join MEMBER_APP_PURCHASED OTHER_MEMBER_APP_PURCHASED
            on OTHER_MEMBER_APP_PURCHASED.APP_ID = THIS_MEMBER_APP.Application
       join MEMBER OTHER_MEMBER on OTHER_MEMBER_APP_PURCHASED.MEMBER_ID = OTHER_MEMBER.ID
where OTHER_MEMBER.NAME != THIS_MEMBER_APP.Member

-- returns unpopular (not installed by anybody) applications (promote them?)
select distinct APP.NAME as Application
from APP APP
       join APP_VER APP_VER on APP.ID = APP_VER.APP_ID
where not exists(select *
                 from MEMBER_APP_INSTALLED MEMBER_APP_INSTALLED
                 where MEMBER_APP_INSTALLED.APP_VER_ID = APP_VER.ID)
order by Application

-- show the most trending applications made by the respective company
select APP.NAME as Application, count(*) as Installs
from APP APP
       join COMPANY COMPANY on APP.COMPANY_ID = COMPANY.ID
       join APP_VER APP_VER on APP.ID = APP_VER.APP_ID
       join MEMBER_APP_INSTALLED MEMBER_APP_INSTALLED on APP_VER.ID = MEMBER_APP_INSTALLED.APP_VER_ID
where COMPANY.NAME = 'Skibox 37'
group by APP.NAME
order by Installs desc

-- returns follower-followed pairs
select M2.NAME as Follower, M1.NAME as Followed
from FOLLOWED_MEMBER FOLLOWED_MEMBER
       join MEMBER M1 on FOLLOWED_MEMBER.FOLLOWED_MEMBER_ID = M1.ID
       join MEMBER M2 on FOLLOWED_MEMBER.FOLLOWING_MEMBER_ID = M2.ID

