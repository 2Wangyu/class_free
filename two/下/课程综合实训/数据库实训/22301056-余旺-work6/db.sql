-- 创建 Users 表
CREATE TABLE Users (
    UserID INT AUTO_INCREMENT PRIMARY KEY,
    Username VARCHAR(255) NOT NULL,
    Password VARCHAR(255) NOT NULL,
    Email VARCHAR(255) NOT NULL,
    Phonenumber VARCHAR(255) NOT NULL
);

-- 创建 ShippingInfo 表
CREATE TABLE ShippingInfo (
    AddressID INT AUTO_INCREMENT PRIMARY KEY,
    UserID INT,
    RecipientName VARCHAR(255) NOT NULL,
    Phone VARCHAR(255) NOT NULL,
    Address VARCHAR(255) NOT NULL,
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
);

-- 创建 Payments 表
CREATE TABLE Payments (
    PaymentID INT AUTO_INCREMENT PRIMARY KEY,
    UserID INT,
    PaymentMethod VARCHAR(50) NOT NULL,
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
);

-- 创建 Orders 表
CREATE TABLE Orders (
    OrderID INT AUTO_INCREMENT PRIMARY KEY,
    UserID INT,
    AddressID INT,
    PaymentID INT,
    TotalAmount DECIMAL(10, 2) NOT NULL,
    OrderDate DATE NOT NULL,
    OrderStatus VARCHAR(50) NOT NULL,
    FOREIGN KEY (UserID) REFERENCES Users(UserID),
    FOREIGN KEY (AddressID) REFERENCES ShippingInfo(AddressID),
    FOREIGN KEY (PaymentID) REFERENCES Payments(PaymentID)
);

-- 创建 ShoppingCart 表
CREATE TABLE ShoppingCart (
    CartID INT AUTO_INCREMENT PRIMARY KEY,
    UserID INT,
    ShoppingQuantity INT NOT NULL,
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
);

-- 创建 Products 表
CREATE TABLE Products (
    ProductID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(50) NOT NULL,
    Price DECIMAL(10, 2) NOT NULL,
    Description TEXT NOT NULL,
    StockQuantity DECIMAL(10, 2) NOT NULL,
    Category VARCHAR(50) NOT NULL
);

-- 创建 OrderDetails 表
CREATE TABLE OrderDetails (
    OrderDetailsID INT AUTO_INCREMENT PRIMARY KEY,
    ProductID INT,
    OrderID INT,
    FOREIGN KEY (ProductID) REFERENCES Products(ProductID),
    FOREIGN KEY (OrderID) REFERENCES Orders(OrderID)
);

-- 创建 CartDetails 表
CREATE TABLE CartDetails (
    CartDetailsID INT AUTO_INCREMENT PRIMARY KEY,
    ProductID INT,
    CartID INT,
    FOREIGN KEY (ProductID) REFERENCES Products(ProductID),
    FOREIGN KEY (CartID) REFERENCES ShoppingCart(CartID)
);

-- 创建 Reviews 表
CREATE TABLE Reviews (
    ReviewID INT AUTO_INCREMENT PRIMARY KEY,
    OrderID INT,
    ReviewDate DATE NOT NULL,
    Content TEXT NOT NULL,
    FOREIGN KEY (OrderID) REFERENCES Orders(OrderID)
);

-- 创建 Sellers 表
CREATE TABLE Sellers (
    SellerID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    Phone VARCHAR(50) NOT NULL,
    Email VARCHAR(50) NOT NULL
);

-- 创建 SupportStaff 表
CREATE TABLE SupportStaff (
    StaffID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    ContactInfo VARCHAR(255) NOT NULL,
    Status VARCHAR(255) NOT NULL,
    UserID INT,
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
);

-- 创建 Logistics 表
CREATE TABLE Logistics (
    LogisticsID INT AUTO_INCREMENT PRIMARY KEY,
    OrderID INT,
    SellerID INT,
    Status VARCHAR(50) NOT NULL,
    FOREIGN KEY (OrderID) REFERENCES Orders(OrderID),
    FOREIGN KEY (SellerID) REFERENCES Sellers(SellerID)
);

-- 创建 AfterSales 表
CREATE TABLE AfterSales (
    AfterSalesID INT AUTO_INCREMENT PRIMARY KEY,
    OrderID INT,
    SupportStaffID INT,
    Content TEXT NOT NULL,
    Result TEXT NOT NULL,
    ResolutionDate DATE NOT NULL,
    FOREIGN KEY (OrderID) REFERENCES Orders(OrderID),
    FOREIGN KEY (SupportStaffID) REFERENCES SupportStaff(StaffID)
);




