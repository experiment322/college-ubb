USE master
GO
IF(EXISTS(SELECT * FROM sys.databases WHERE name='Subiectul32019'))
    DROP DATABASE Subiectul32019;
GO
CREATE DATABASE Subiectul32019;
GO
USE Subiectul32019;
GO
CREATE TABLE Bucatari
(
    cod_bucatar INT PRIMARY KEY IDENTITY,
    nume NVARCHAR(200),
    prenume NVARCHAR(200),
    data_nasterii DATE,
    website NVARCHAR(200)
);
CREATE TABLE UnitatiDeMasura
(
    cod_unitate INT PRIMARY KEY IDENTITY,
    nume_unitate NVARCHAR(200)
);
CREATE TABLE Supe
(
    cod_supa INT PRIMARY KEY IDENTITY,
    nume_supa NVARCHAR(200),
    mod_de_preparare NVARCHAR(3000),
    cod_bucatar INT FOREIGN KEY REFERENCES Bucatari(cod_bucatar)
        ON UPDATE CASCADE ON DELETE CASCADE
);
CREATE TABLE Ingrediente
(
    cod_ingredient INT PRIMARY KEY IDENTITY,
    nume_ingredient NVARCHAR(200),
    descriere NVARCHAR(1000)
);
CREATE TABLE Retete
(
    cod_supa INT FOREIGN KEY REFERENCES Supe(cod_supa)
        ON UPDATE CASCADE ON DELETE CASCADE,
    cod_ingredient INT FOREIGN KEY REFERENCES Ingrediente(cod_ingredient)
        ON UPDATE CASCADE ON DELETE CASCADE,
    cod_unitate INT FOREIGN KEY REFERENCES UnitatiDeMasura(cod_unitate)
        ON UPDATE CASCADE ON DELETE CASCADE,
    cantitate REAL,
    CONSTRAINT pk_Reteta PRIMARY KEY (cod_supa,cod_ingredient)
);
--Bucatari
INSERT INTO Bucatari (nume,prenume,data_nasterii,website) VALUES
('Pop','Andrei','1991-03-10','www.popandrei.com');
INSERT INTO Bucatari (nume,prenume,data_nasterii,website) VALUES
('Popa','Oana','1988-05-12','www.popaoana.com');
INSERT INTO Bucatari (nume,prenume,data_nasterii,website) VALUES
('Popescu','Bogdan','1981-10-20','www.popescubogdan.com');
--Supe bucatar 1
INSERT INTO Supe (nume_supa,mod_de_preparare,cod_bucatar) VALUES
('supa 1 Andrei','mod de preparare supa 1 Andrei',1);
INSERT INTO Supe (nume_supa,mod_de_preparare,cod_bucatar) VALUES
('supa 2 Andrei','mod de preparare supa 2 Andrei',1);
INSERT INTO Supe (nume_supa,mod_de_preparare,cod_bucatar) VALUES
('supa 3 Andrei','mod de preparare supa 3 Andrei',1);
--Supe bucatar 2
INSERT INTO Supe (nume_supa,mod_de_preparare,cod_bucatar) VALUES
('supa 1 Oana','mod de preparare supa 1 Oana',2);
INSERT INTO Supe (nume_supa,mod_de_preparare,cod_bucatar) VALUES
('supa 2 Oana','mod de preparare supa 2 Oana',2);
INSERT INTO Supe (nume_supa,mod_de_preparare,cod_bucatar) VALUES
('supa 3 Oana','mod de preparare supa 3 Oana',2);
--Supe bucatar 3
INSERT INTO Supe (nume_supa,mod_de_preparare,cod_bucatar) VALUES
('supa 1 Bogdan','mod de preparare supa 1 Bogdan',3);
INSERT INTO Supe (nume_supa,mod_de_preparare,cod_bucatar) VALUES
('supa 2 Bogdan','mod de preparare supa 2 Bogdan',3);
INSERT INTO Supe (nume_supa,mod_de_preparare,cod_bucatar) VALUES
('supa 3 Bogdan','mod de preparare supa 3 Bogdan',3);
--Ingrediente
INSERT INTO Ingrediente (nume_ingredient,descriere) VALUES
('ceapa','descriere ceapa');
INSERT INTO Ingrediente (nume_ingredient,descriere) VALUES
('morcov','descriere morcov');
INSERT INTO Ingrediente (nume_ingredient,descriere) VALUES
('mazare','descriere mazare');
--Unitati de masura
INSERT INTO UnitatiDeMasura (nume_unitate) VALUES ('kilogram');
INSERT INTO UnitatiDeMasura (nume_unitate) VALUES ('litru');
INSERT INTO UnitatiDeMasura (nume_unitate) VALUES ('lingura');
--Reteta
INSERT INTO Retete (cod_supa,cod_ingredient,cod_unitate,cantitate) VALUES
(1,1,1,0.2);
INSERT INTO Retete (cod_supa,cod_ingredient,cod_unitate,cantitate) VALUES
(1,2,1,1);
INSERT INTO Retete (cod_supa,cod_ingredient,cod_unitate,cantitate) VALUES
(1,3,1,1);
