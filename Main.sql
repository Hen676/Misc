-- Create Database

DROP DATABASE IF EXISTS Main;

CREATE DATABASE Main;
USE Main;

START TRANSACTION;


-- Create Tables

DROP TABLE IF EXISTS address;
DROP TABLE IF EXISTS customer;
DROP TABLE IF EXISTS customer_invoice;
DROP TABLE IF EXISTS customer_order;
DROP TABLE IF EXISTS garden_centre;
DROP TABLE IF EXISTS purchase_order;
DROP TABLE IF EXISTS staff;
DROP TABLE IF EXISTS stock;
DROP TABLE IF EXISTS supplier;

CREATE TABLE address (
	address_id int(11) NOT NULL AUTO_INCREMENT,
	line_1 varchar(60) NOT NULL,
	line_2 varchar(60) DEFAULT NULL,
	city varchar(30) NOT NULL,
	postcode varchar(15) NOT NULL,
	PRIMARY KEY (address_id)
);

CREATE TABLE customer (
	email varchar(255) NOT NULL,
	first_name varchar(60) NOT NULL,
	last_name varchar(60) NOT NULL,
	telephone varchar(20) NOT NULL,
	date_birth date NOT NULL,
	address_id int(11) NOT NULL,
	invoice_number int(11) NOT NULL,
	customer_order_id int(11) NOT NULL,
	PRIMARY KEY (email)
);

CREATE TABLE customer_invoice (
	invoice_number int(11) NOT NULL AUTO_INCREMENT,
	staff_email varchar(255) NOT NULL,
	payment_date date NOT NULL,
	order_price int(11) NOT NULL,
	order_price_discount int(11) NOT NULL,
	order_quantity int(11) NOT NULL,
	stock_name_1 varchar(255) NOT NULL,
	stock_name_2 varchar(255) NOT NULL,
	order_date date NOT NULL,
	PRIMARY KEY (invoice_number)
);

CREATE TABLE customer_order (
	customer_order_id int(11) NOT NULL AUTO_INCREMENT,
	order_status varchar(10) NOT NULL,
	order_date date NOT NULL,
	stock_name_1 varchar(255) NOT NULL,
	stock_name_2 varchar(255) NOT NULL,
	order_quantity int(11) NOT NULL,
	order_price_discount int(11) NOT NULL,
	order_price int(11) NOT NULL,
	PRIMARY KEY (customer_order_id)
);

CREATE TABLE garden_centre (
	address_id int(11) NOT NULL,
	company_id int(11) NOT NULL,
	telephone varchar(20) NOT NULL,
	PRIMARY KEY (telephone)
);

CREATE TABLE purchase_order (
	purchase_order_id int(11) NOT NULL AUTO_INCREMENT,
	purchase_status varchar(10) NOT NULL,
	purchase_date date NOT NULL,
	purchase_quantity int(11) NOT NULL,
	purchase_item int(11) NOT NULL,
	purchase_price int(11) NOT NULL,
	supplier varchar(255) NOT NULL,
	PRIMARY KEY (purchase_order_id)
);

CREATE TABLE staff (
	email varchar(255) NOT NULL,
	first_name varchar(60) NOT NULL,
	last_name varchar(60) NOT NULL,
	telephone varchar(20) NOT NULL,
	date_birth date NOT NULL,
	address_id int(11) NOT NULL,
	qualifications text NOT NULL,
	sortcode int(3) NOT NULL,
	name_on_card varchar(30) NOT NULL,
	card_number varchar(19) NOT NULL,
	PRIMARY KEY (email)
);

CREATE TABLE stock (
	name_latin varchar(255) NOT NULL,
	name_popular varchar(255) NOT NULL,
	attributes_colour varchar(255) DEFAULT NULL,
	attributes_flowering_period varchar(255) DEFAULT NULL,
	attributes_dimensions varchar(255) DEFAULT NULL,
	advice_soil_type varchar(255) DEFAULT NULL,
	advice_moisture varchar(255) DEFAULT NULL,
	advice_sunlight varchar(255) DEFAULT NULL,
	season varchar(255) DEFAULT NULL,
	description text NOT NULL,
	address_id int(11) NOT NULL,
	CONSTRAINT stock_name PRIMARY KEY (name_latin,name_popular)
);

CREATE TABLE supplier (
	email varchar(255) NOT NULL,
	name varchar(255) NOT NULL,
	telephone varchar(20) NOT NULL,
	PRIMARY KEY (email)
);

-- Add/Connect Forign keys
  
ALTER TABLE customer
	ADD FOREIGN KEY (address_id) REFERENCES address (address_id),
	ADD FOREIGN KEY (customer_order_id) REFERENCES customer_order (customer_order_id),
	ADD FOREIGN KEY (invoice_number) REFERENCES customer_invoice (invoice_number);

ALTER TABLE garden_centre
	ADD FOREIGN KEY (address_id) REFERENCES address (address_id);

ALTER TABLE staff
	ADD FOREIGN KEY (address_id) REFERENCES address (address_id);

ALTER TABLE stock
	ADD FOREIGN KEY (address_id) REFERENCES address (address_id);
	
ALTER TABLE customer_invoice
	ADD CONSTRAINT customer_invoice_stock FOREIGN KEY (stock_name_1, stock_name_2) REFERENCES stock (name_latin,name_popular),
	ADD FOREIGN KEY (staff_email) REFERENCES staff (email);

ALTER TABLE customer_order
	ADD CONSTRAINT customer_order_stock FOREIGN KEY (stock_name_1, stock_name_2) REFERENCES stock (name_latin,name_popular);
	
ALTER TABLE purchase_order
	ADD FOREIGN KEY (supplier) REFERENCES supplier (email);
	
-- Insert data for garden centre and stock.

SET FOREIGN_KEY_CHECKS=0;

INSERT INTO address (line_1, city, postcode)
	values ('7 Lake Rd','lincoln','LN5 3LG');
INSERT INTO garden_centre (address_id, company_id, telephone)
	values (LAST_INSERT_ID(),50349324,'07700900113');
INSERT INTO stock (address_id, name_latin, name_popular, attributes_colour, attributes_flowering_period, attributes_dimensions, advice_soil_type, advice_moisture, advice_sunlight, season, description)
	values (LAST_INSERT_ID(),'Bishop of Llandaff','Dahlia','Red','July to September','0.45x1.1x0.45','humus-rich soil','','full sun','Summer','It is a flower'),
	(LAST_INSERT_ID(),'Rosa Peace','Rosa','white','July to September','1x1.2x1','humus-rich soil','moist','full sun','Summer','It is a flower');

INSERT INTO address (line_1, city, postcode)
	values ('5 Mary Rd','lincoln','LN6 3TN');
INSERT INTO garden_centre (address_id, company_id, telephone)
	values (LAST_INSERT_ID(),50378784,'07700933113');
INSERT INTO stock (address_id, name_latin, name_popular, attributes_colour, attributes_flowering_period, attributes_dimensions, advice_soil_type, advice_moisture, advice_sunlight, season, description)
	values (LAST_INSERT_ID(),'shed','shed','Blue','','1.79x1.64x2.37','','','','','It is a shed, what more do u want to know');
	
-- Insert data for customer (invoices and orders)
	
	-- Customers with orders

INSERT INTO address (line_1, city, postcode)
	values ('59 Capmartin Rd', 'Coventry', 'CV6 3FW');
INSERT INTO customer (address_id, first_name, last_name, telephone, date_birth, email)
	values (LAST_INSERT_ID(),'Harry','Brown','07700900779','1819-12-14', 'Harry.Brown@gmail.com');
INSERT INTO customer_order (order_status, order_date, stock_name_1, stock_name_2, order_quantity, order_price_discount, order_price)
	values ('Dispatched','2018-1-16', 'shed', 'shed', 2, 0, 240);
INSERT INTO customer_invoice (invoice_number, payment_date, order_price, order_price_discount, order_quantity, stock_name_1, stock_name_2, order_date)
	values (LAST_INSERT_ID(),'2018-1-19', 240, 0, 2, 'shed', 'shed', '2018-1-16');
UPDATE customer 
SET invoice_number = LAST_INSERT_ID(), customer_order_id = LAST_INSERT_ID()
WHERE email = 'Harry.Brown@gmail.com';
	
INSERT INTO address (line_1, city, postcode)
	values ('36-38 Chesterfield Rd', 'Dronfield', 'S18 2XB');
INSERT INTO customer (address_id, first_name, last_name, telephone, date_birth, email)
	values (LAST_INSERT_ID(),'Larry','Crown','07710988779','1989-1-17', 'Larry.Crown@gmail.com');
INSERT INTO customer_order ( order_status, order_date, stock_name_1, stock_name_2, order_quantity, order_price_discount, order_price)
	values ('Dispatched','2018-1-16', 'Rosa Peace', 'Rosa', 1, 0, 23);
INSERT INTO customer_invoice (invoice_number, payment_date, order_price, order_price_discount, order_quantity, stock_name_1, stock_name_2, order_date)
	values (LAST_INSERT_ID(),'2018-1-19', 23, 0, 1, 'Rosa Peace', 'Rosa', '2018-1-16');
UPDATE customer 
SET invoice_number = LAST_INSERT_ID(), customer_order_id = LAST_INSERT_ID()
WHERE email = 'Larry.Crown@gmail.com';

INSERT INTO address (line_1, city, postcode)
	values ('8 Hackworth Gardens', 'Wylam', 'NE41 8EJ');
INSERT INTO customer (address_id, first_name, last_name, telephone, date_birth, email)
	values (LAST_INSERT_ID(),'Barry','Frown','07710968749','1986-4-27', 'Barry.Frown@gmail.com');
INSERT INTO customer_order (order_status, order_date, stock_name_1, stock_name_2, order_quantity, order_price_discount, order_price)
	values ('Dispatched','2018-1-16', 'shed', 'shed', 1, 0, 120);
INSERT INTO customer_invoice (invoice_number, payment_date, order_price, order_price_discount, order_quantity, stock_name_1, stock_name_2, order_date)
	values (LAST_INSERT_ID(),'2018-1-19', 120, 0, 1, 'shed', 'shed', '2018-1-16');
UPDATE customer 
SET invoice_number = LAST_INSERT_ID(), customer_order_id = LAST_INSERT_ID()
WHERE email = 'Barry.Frown@gmail.com';
	
	-- Other Customers
	
INSERT INTO address (line_1, city, postcode)
	values ('16 Forum Cl', 'London', 'E3 2FD');
INSERT INTO customer (address_id, first_name, last_name, telephone, date_birth, email)
	values (LAST_INSERT_ID(),'David','Smith','07710486749','1929-12-27', 'David.Smith@gmail.com');
	
INSERT INTO address (line_1, city, postcode)
	values ('2 North St', 'Beaworthy', 'EX21 5NQ');
INSERT INTO customer (address_id, first_name, last_name, telephone, date_birth, email)
	values (LAST_INSERT_ID(),'Sarah','Brown','07714386749','1990-5-21', 'Sarah.Brown@gmail.com');
	
INSERT INTO address (line_1, city, postcode)
	values ('36 Alfred Ave', 'Bedlington', 'NE22 5AZ');
INSERT INTO customer (address_id, first_name, last_name, telephone, date_birth, email)
	values (LAST_INSERT_ID(),'Cathrine','Kasper','','1982-2-06', 'Cathrine.Kasper@gmail.com');
	
INSERT INTO address (line_1, city, postcode)
	values ('71 Heaton Rd', 'Bolton', 'BL6');
INSERT INTO customer (address_id, first_name, last_name, telephone, date_birth, email)
	values (LAST_INSERT_ID(),'Sela','Jalil','07712345749','1991-Jun-21', 'Sela.Jalil@gmail.com');
	
INSERT INTO address (line_1, city, postcode)
	values ('112 Warstones Dr', 'Wolverhampton ', 'WV4 4NB');
INSERT INTO customer (address_id, first_name, last_name, telephone, date_birth, email)
	values (LAST_INSERT_ID(),'Chandra','Cola','07714567749','1994-1-01', 'Chandra.Cola@gmail.com');
	
INSERT INTO address (line_1, line_2, city, postcode)
	values ('8 Rufford Cl', 'Yeadon', 'Leeds', 'CV6 3FW');
INSERT INTO customer (address_id, first_name, last_name, telephone, date_birth, email)
	values (LAST_INSERT_ID(),'Edna','Đuro','07714384567','1986-4-14', 'Edna.Đuro@gmail.com');
	
INSERT INTO address (line_1, line_2, city, postcode)
	values ('Not Real', 'Woldingham', 'Caterham', 'CR3 7LS');
INSERT INTO customer (first_name, last_name, telephone, date_birth, email)
	values ('Wibo','Machlah','07714345649','1994-Dec-30', 'Wibo.Machlah@gmail.com');
	
-- Updata Customer
	
UPDATE customer
	SET address_id = LAST_INSERT_ID()
	WHERE first_name = 'Wibo';
DELETE FROM address
	WHERE line_1 = 'Not Real';
	
SET FOREIGN_KEY_CHECKS=1;
	
-- Insert data for staff

INSERT INTO address (line_1, line_2, city, postcode)
	values ('Lane Bane', 'Woldingham', 'Caterham', 'CR3 7LS');
INSERT INTO staff (address_id, email, first_name, last_name, telephone, date_birth, qualifications, sortcode, name_on_card, card_number)
	values (LAST_INSERT_ID(),'g.vilma@gmail.com','Gordana','Vilma','07714345649','1994-12-30','10 GCSEs and 2 A-levels',123,'Gordana L Vilma','4716992409780595');
	
INSERT INTO address (line_1, city, postcode)
	values ('Rain Fain', 'Holdington', 'CR3 7LS');
INSERT INTO staff (address_id, email, first_name, last_name, telephone, date_birth, qualifications, sortcode, name_on_card, card_number)
	values (LAST_INSERT_ID(),'frida.a@hotmail.co.uk','Frida','Anĉjo','07714345649','1994-12-30','3 O-levels',723,'Frida Anĉjo','4556985549732578');
	
INSERT INTO address (line_1, city, postcode)
	values ('Rojer Walk', 'PACKERSTINE','CR3 7LS');
INSERT INTO staff (address_id, email, first_name, last_name, telephone, date_birth, qualifications, sortcode, name_on_card, card_number)
	values (LAST_INSERT_ID(),'ethan.amrita@BTinternet.co.uk','Ethan','Amrita','07714345649','1994-12-30','4 GCSEs',143,'Ethan K Amrita','4539838592646397');
	
-- Insert data for supplier

SET FOREIGN_KEY_CHECKS=0;

INSERT INTO supplier (email, name, telephone)
	values ('Order.Mach@Mach-Email.com','Mach','07714234649');
INSERT INTO purchase_order (purchase_status, purchase_date, purchase_quantity, purchase_item, purchase_price)
	values ('Delivered', '2017-Dec-30', 3, 9, 13);
INSERT INTO purchase_order (purchase_status, purchase_date, purchase_quantity, purchase_item, purchase_price)
	values ('Dispatched', '2018-Jan-15', 1, 3, 17);

	
INSERT INTO supplier (email, name, telephone)
	values ('Order.GarryField@GarryField-Email.com','GarryField','07714323449');
INSERT INTO purchase_order (purchase_status, purchase_date, purchase_quantity, purchase_item, purchase_price)
	values ('Dispatched', '2018-Jan-17', 12, 4, 102);

	
SET FOREIGN_KEY_CHECKS=1;
	
-- Join and Union
	
	-- inner join see garden centre and there address.
	
SELECT address.line_1, address.line_2, address.city, address.postcode, garden_centre.address_id
FROM address
INNER JOIN garden_centre on garden_centre.address_id = address.address_id;
	
	-- left join for seing orderID and the customers name
	
SELECT customer_order.customer_order_id, customer.first_name, customer.last_name
FROM customer
LEFT JOIN customer_order on customer_order.customer_order_id = customer.customer_order_id;

	-- right join for seing invoice number and the customers name
	
SELECT customer_invoice.invoice_number, customer.first_name, customer.last_name
FROM customer_invoice
RIGHT JOIN customer on customer_invoice.invoice_number = customer.invoice_number;
	
	-- union for customer email and there postcode
	
SELECT email FROM customer
UNION
SELECT postcode FROM address;
	
-- Copy database

	-- Drop tables if exist
	
DROP TABLE IF EXISTS copy_of_address;
DROP TABLE IF EXISTS copy_of_customer;
DROP TABLE IF EXISTS copy_of_customer_invoice;
DROP TABLE IF EXISTS copy_of_customer_order;
DROP TABLE IF EXISTS copy_of_garden_centre;
DROP TABLE IF EXISTS copy_of_purchase_order;
DROP TABLE IF EXISTS copy_of_staff;
DROP TABLE IF EXISTS copy_of_stock;
DROP TABLE IF EXISTS copy_of_supplier;

	-- create duplicate tables
	
CREATE TABLE copy_of_address LIKE address;
INSERT copy_of_address SELECT * FROM address;

CREATE TABLE copy_of_customer LIKE customer;
INSERT copy_of_customer SELECT * FROM customer;

CREATE TABLE copy_of_customer_invoice LIKE customer_invoice;
INSERT copy_of_customer_invoice SELECT * FROM customer_invoice;

CREATE TABLE copy_of_customer_order LIKE customer_order;
INSERT copy_of_customer_order SELECT * FROM customer_order;

CREATE TABLE copy_of_garden_centre LIKE garden_centre;
INSERT copy_of_garden_centre SELECT * FROM garden_centre;

CREATE TABLE copy_of_purchase_order LIKE purchase_order;
INSERT copy_of_purchase_order SELECT * FROM purchase_order;

CREATE TABLE copy_of_staff LIKE staff;
INSERT copy_of_staff SELECT * FROM staff;

CREATE TABLE copy_of_stock LIKE stock;
INSERT copy_of_stock SELECT * FROM stock;

CREATE TABLE copy_of_supplier LIKE supplier;
INSERT copy_of_supplier SELECT * FROM supplier;

-- Read user

DROP USER IF EXISTS root;
flush PRIVILEGES;

CREATE USER root;
GRANT SELECT ON main.* TO root;

-- Finalise / Save

COMMIT;