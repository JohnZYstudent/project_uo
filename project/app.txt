use trans69;
#1 what items be ordered in that month
select i.item_num, i.description from items i
join orders o using(item_num)
where o.order_date like "10%";
#2 what items under specific courier's hand
select i.item_num, i.description from items i 
join orders o using(item_num)
join transLocation t on o.area = t.city
join couriers c on t.location_num = c.area
join drivers d using(driver_license)
join employees e using(ssn)
where concat(e.fname," ",e.lname)  = "Yimin Ni";
#3 what item customer order
select i.item_num, i.description, i.special_option from items i
join orders o using(item_num)
join customers c on o.cust_num = c.cust_id
where concat(c.fname," ",c.lname) = "David Wood";
#4 how many cust serv call made in specfic month
select count(*) from serviceRecord s
where s.date like "10%";
#5 what calls were handled by specific employee
select s.service_num, s.start_time, s.end_time, s.date from serviceRecord s
join employees e using(ssn)
where concat(e.fname, " ", e.lname) = "Ni Jin";
#6 who deliever the customer's items
select concat(e.fname," ",e.lname) as name from employees e
join drivers d using(ssn)
join couriers c using(driver_license)
join transLocation t on c.area = t.location_num
join orders o on t.city = o.area
join customers cus on o.cust_num = cus.cust_id
where concat(cus.fname," ",cus.lname) = "John Zhou";
#7 search car under specific driver
select v.plate_num, v.model, v.year, v.size from employees e
join drivers d using(ssn)
join vehicles v using(plate_num)
where concat(e.fname," ",e.lname) = "Powell Harold";
#8 check specific employee's salary
select concat(e.fname," ",e.lname) as name, e.salary from employees e
where concat(e.fname," ",e.lname) = "Yimin Ni";
#9 search driver who drive specific car
select concat(e.fname," ",e.lname) as name from employees e
join drivers d using(ssn)
where d.plate_num = "DIR039";
#10 search for employee's information
select * from employees e
where concat(e.fname," ",e.lname) = "Yimin Ni";
#11 search for customer's information
select * from customers c
where concat(c.fname," ",c.lname) = "John Zhou";
#12 which truckdrivers will pass specific translocation
select concat(e.fname," ",e.lname)as name from employees e
join drivers d using(ssn)
join truckDrivers t using(driver_license)
where t.location_start <= 3 and t.location_end >= 3;