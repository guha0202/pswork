-- MySQL Script generated by MySQL Workbench
-- Thu Jun  6 20:36:34 2024
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `mydb` ;

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`PrevCompany`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`PrevCompany` ;

CREATE TABLE IF NOT EXISTS `mydb`.`PrevCompany` (
  `prevCompanyNo` INT NOT NULL,
  `pCompanyName` VARCHAR(255) NULL,
  `pCompanyNo` VARCHAR(255) NULL,
  `pCompanyTelNo` VARCHAR(20) NULL,
  `pCompanyFaxNo` VARCHAR(20) NULL,
  `pCompanyStreet` VARCHAR(255) NULL,
  `pCompanyCity` VARCHAR(255) NULL,
  `pCompanyState` VARCHAR(255) NULL,
  `pCompanyZipCode` VARCHAR(20) NULL,
  `pCompanyWebAddress` VARCHAR(255) NULL,
  `contactName` VARCHAR(255) NULL,
  `contactEmailAddress` VARCHAR(255) NULL,
  PRIMARY KEY (`prevCompanyNo`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Employee`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Employee` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Employee` (
  `EmployeeNo` INT NOT NULL,
  `position` VARCHAR(255) NULL,
  `Employeecol` VARCHAR(45) NULL,
  `empEmailAddress` VARCHAR(255) NULL,
  `address` VARCHAR(255) NULL,
  `firstName` VARCHAR(255) NULL,
  `title` VARCHAR(255) NULL,
  `middleName` VARCHAR(255) NULL,
  `lastName` VARCHAR(255) NULL,
  `workTelExt` VARCHAR(20) NULL,
  `homeTelNo` VARCHAR(20) NULL,
  `socialSecurityNumber` VARCHAR(20) NULL,
  `DOB` DATE NULL,
  `sex` CHAR(1) NULL,
  `salary` DECIMAL(10,2) NULL,
  `dateStarted` DATE NULL,
  `dateLeft` DATE NULL,
  `departmentNo` INT NULL,
  `supervisorEmployeeNo` INT NULL,
  `Department_DepartmentNo` INT NOT NULL,
  `Department_Employee_EmployeeNo` INT NOT NULL,
  `Employee_EmployeeNo` INT NOT NULL,
  PRIMARY KEY (`EmployeeNo`),
  UNIQUE INDEX `socialSecurityNumber_UNIQUE` (`socialSecurityNumber` ASC) VISIBLE,
  INDEX `fk_Employee_Department1_idx` (`Department_DepartmentNo` ASC, `Department_Employee_EmployeeNo` ASC) VISIBLE,
  INDEX `fk_Employee_Employee1_idx` (`supervisorEmployeeNo` ASC) VISIBLE,
  CONSTRAINT `fk_Employee_Department1`
    FOREIGN KEY (`Department_DepartmentNo` , `Department_Employee_EmployeeNo`)
    REFERENCES `mydb`.`Department` (`DepartmentNo` , `Employee_EmployeeNo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Employee_Employee1`
    FOREIGN KEY (`supervisorEmployeeNo`)
    REFERENCES `mydb`.`Employee` (`EmployeeNo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Department`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Department` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Department` (
  `DepartmentNo` INT NOT NULL,
  `deptLocation` VARCHAR(255) NULL,
  `departmentName` VARCHAR(255) NULL,
  `Departmentcol` VARCHAR(45) NULL,
  `managerEmployeeNo` INT NULL,
  `Employee_EmployeeNo` INT NOT NULL,
  PRIMARY KEY (`DepartmentNo`, `Employee_EmployeeNo`),
  INDEX `fk_Department_Employee_idx` (`Employee_EmployeeNo` ASC) VISIBLE,
  CONSTRAINT `fk_Department_Employee`
    FOREIGN KEY (`Employee_EmployeeNo`)
    REFERENCES `mydb`.`Employee` (`EmployeeNo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`PositionType`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`PositionType` ;

CREATE TABLE IF NOT EXISTS `mydb`.`PositionType` (
  `positionTypeNo` INT NOT NULL,
  `positionTypeDescription` VARCHAR(255) NULL,
  PRIMARY KEY (`positionTypeNo`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Grade`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Grade` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Grade` (
  `gradeNo` INT NOT NULL,
  `vaildFromDate` DATE NULL,
  `vaildToDate` DATE NULL,
  `gradeDescription` VARCHAR(255) NULL,
  `gradeSalary` DECIMAL(10,2) NULL,
  `noDaysLeaveEntitlement` INT NULL,
  `positionTypeNo` INT NULL,
  `PositionType_positionTypeNo` INT NOT NULL,
  PRIMARY KEY (`gradeNo`, `PositionType_positionTypeNo`),
  INDEX `fk_Grade_PositionType1_idx` (`PositionType_positionTypeNo` ASC) VISIBLE,
  CONSTRAINT `fk_Grade_PositionType1`
    FOREIGN KEY (`PositionType_positionTypeNo`)
    REFERENCES `mydb`.`PositionType` (`positionTypeNo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Post`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Post` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Post` (
  `postNo` INT NOT NULL,
  `freeLaborStandardActExempt` CHAR(1) NULL COMMENT '假设 freeLaborStandardActExempt 是一个表示是否免除劳动标准法规定的字符类型（例如 \'Y\' 或 \'N\'）',
  `salariedHourly` CHAR(1) NULL COMMENT '假设 salariedHourly 是一个表示是否为薪水制的小时工作的字符类型（例如 \'Y\' 或 \'N\')',
  `availableFromDate` DATE NOT NULL,
  `availableToDate` DATE NULL,
  `postDescription` VARCHAR(255) NULL,
  `fullPartTime` CHAR(1) NULL COMMENT '假设 fullPartTime 是一个表示全职或兼职的字符类型（例如 \'F\' 或 \'P\'）',
  `temporaryPermanent` CHAR(1) NULL COMMENT '假设 temporaryPermanent 是一个表示临时或永久职位的字符类型（例如 \'T\' 或 \'P\'）',
  `departmentNo` INT NULL,
  `Department_DepartmentNo` INT NOT NULL,
  `Department_Employee_EmployeeNo` INT NOT NULL,
  PRIMARY KEY (`postNo`, `Department_DepartmentNo`, `Department_Employee_EmployeeNo`, `availableFromDate`),
  INDEX `fk_Post_Department1_idx` (`Department_DepartmentNo` ASC, `Department_Employee_EmployeeNo` ASC) VISIBLE,
  CONSTRAINT `fk_Post_Department1`
    FOREIGN KEY (`Department_DepartmentNo` , `Department_Employee_EmployeeNo`)
    REFERENCES `mydb`.`Department` (`DepartmentNo` , `Employee_EmployeeNo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`GradePost`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`GradePost` ;

CREATE TABLE IF NOT EXISTS `mydb`.`GradePost` (
  `gradeNo` INT NOT NULL,
  `vaildFromDate` DATE NOT NULL,
  `postNo` INT NOT NULL,
  `availbleFromDate` DATE NOT NULL,
  `Grade_gradeNo` INT NOT NULL,
  `Grade_PositionType_positionTypeNo` INT NOT NULL,
  `Post_postNo` INT NOT NULL,
  PRIMARY KEY (`gradeNo`, `vaildFromDate`, `postNo`, `availbleFromDate`, `Grade_gradeNo`, `Grade_PositionType_positionTypeNo`, `Post_postNo`),
  INDEX `fk_GradePost_Grade1_idx` (`Grade_gradeNo` ASC, `Grade_PositionType_positionTypeNo` ASC) VISIBLE,
  INDEX `fk_GradePost_Post1_idx` (`Post_postNo` ASC) VISIBLE,
  CONSTRAINT `fk_GradePost_Grade1`
    FOREIGN KEY (`Grade_gradeNo` , `Grade_PositionType_positionTypeNo`)
    REFERENCES `mydb`.`Grade` (`gradeNo` , `PositionType_positionTypeNo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_GradePost_Post1`
    FOREIGN KEY (`Post_postNo`)
    REFERENCES `mydb`.`Post` (`postNo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Institution`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Institution` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Institution` (
  `institutionNo` INT NOT NULL,
  `institutionName` VARCHAR(255) NULL,
  `instAddress` VARCHAR(255) NULL,
  `instTelNo` VARCHAR(20) NULL,
  `instFaxNo` VARCHAR(20) NULL,
  `instWebAddress` VARCHAR(255) NULL,
  `contactName` VARCHAR(255) NULL,
  `contactTelNo` VARCHAR(20) NULL,
  `contactFaxNo` VARCHAR(20) NULL,
  `contactEmailAddress` VARCHAR(255) NULL,
  PRIMARY KEY (`institutionNo`),
  UNIQUE INDEX `institutionName_UNIQUE` (`institutionName` ASC) VISIBLE,
  UNIQUE INDEX `instTelNo_UNIQUE` (`instTelNo` ASC) VISIBLE,
  UNIQUE INDEX `instFaxNo_UNIQUE` (`instFaxNo` ASC) VISIBLE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Qualification`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Qualification` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Qualification` (
  `qualificationName` VARCHAR(255) NOT NULL,
  `employeeNo` INT NULL,
  `gradeObtained` VARCHAR(255) NULL,
  `startQualDate` DATE NULL,
  `endQualDate` DATE NULL,
  `gpa` DECIMAL(5,2) NULL,
  `institutionNo` INT NULL,
  `Qualificationcol` VARCHAR(45) NULL,
  `Employee_EmployeeNo` INT NOT NULL,
  `Institution_institutionNo` INT NOT NULL,
  PRIMARY KEY (`qualificationName`, `Institution_institutionNo`),
  INDEX `fk_Qualification_Employee1_idx` (`Employee_EmployeeNo` ASC) VISIBLE,
  INDEX `fk_Qualification_Institution1_idx` (`Institution_institutionNo` ASC) VISIBLE,
  CONSTRAINT `fk_Qualification_Employee1`
    FOREIGN KEY (`Employee_EmployeeNo`)
    REFERENCES `mydb`.`Employee` (`EmployeeNo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Qualification_Institution1`
    FOREIGN KEY (`Institution_institutionNo`)
    REFERENCES `mydb`.`Institution` (`institutionNo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Review`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Review` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Review` (
  `reviewerEmployeeNo` INT NOT NULL,
  `revieweeEmployeeNo` INT NOT NULL,
  `reviewDate` DATE NOT NULL,
  `comments` TEXT NULL,
  `Employee_EmployeeNo` INT NOT NULL,
  `Employee_EmployeeNo1` INT NOT NULL,
  PRIMARY KEY (`reviewerEmployeeNo`, `revieweeEmployeeNo`, `reviewDate`),
  INDEX `fk_Review_Employee2_idx` (`revieweeEmployeeNo` ASC) VISIBLE,
  CONSTRAINT `fk_Review_Employee1`
    FOREIGN KEY (`reviewerEmployeeNo`)
    REFERENCES `mydb`.`Employee` (`EmployeeNo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Review_Employee2`
    FOREIGN KEY (`revieweeEmployeeNo`)
    REFERENCES `mydb`.`Employee` (`EmployeeNo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`WorkHistory`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`WorkHistory` ;

CREATE TABLE IF NOT EXISTS `mydb`.`WorkHistory` (
  `prevCompanyNo` INT NOT NULL,
  `employeeNo` INT NOT NULL,
  `prevPosition` VARCHAR(255) NULL,
  `prevGrade` VARCHAR(255) NULL,
  `prevSalary` DECIMAL(10,2) NULL,
  `prevLocation` VARCHAR(255) NULL,
  `prevResponsibilities` TEXT NULL,
  `WorkHistorycol` VARCHAR(45) NULL,
  `PrevCompany_prevCompanyNo` INT NOT NULL,
  `Employee_EmployeeNo` INT NOT NULL,
  PRIMARY KEY (`prevCompanyNo`, `employeeNo`, `PrevCompany_prevCompanyNo`, `Employee_EmployeeNo`),
  INDEX `fk_WorkHistory_PrevCompany1_idx` (`PrevCompany_prevCompanyNo` ASC) VISIBLE,
  INDEX `fk_WorkHistory_Employee1_idx` (`Employee_EmployeeNo` ASC) VISIBLE,
  CONSTRAINT `fk_WorkHistory_PrevCompany1`
    FOREIGN KEY (`PrevCompany_prevCompanyNo`)
    REFERENCES `mydb`.`PrevCompany` (`prevCompanyNo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_WorkHistory_Employee1`
    FOREIGN KEY (`Employee_EmployeeNo`)
    REFERENCES `mydb`.`Employee` (`EmployeeNo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Position`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Position` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Position` (
  `employeeNo` INT NOT NULL,
  `postNo` INT NOT NULL,
  `startDate` DATE NOT NULL,
  `endDate` DATE NULL,
  `Post_postNo` INT NOT NULL,
  `Post_Department_DepartmentNo` INT NOT NULL,
  `Post_Department_Employee_EmployeeNo` INT NOT NULL,
  `Employee_EmployeeNo` INT NOT NULL,
  PRIMARY KEY (`employeeNo`, `postNo`, `startDate`, `Employee_EmployeeNo`),
  INDEX `fk_Position_Post1_idx` (`Post_postNo` ASC, `startDate` ASC) VISIBLE,
  INDEX `fk_Position_Employee1_idx` (`Employee_EmployeeNo` ASC) VISIBLE,
  CONSTRAINT `fk_Position_Post1`
    FOREIGN KEY (`Post_postNo` , `startDate`)
    REFERENCES `mydb`.`Post` (`postNo` , `availableFromDate`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Position_Employee1`
    FOREIGN KEY (`Employee_EmployeeNo`)
    REFERENCES `mydb`.`Employee` (`EmployeeNo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
