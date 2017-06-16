USE [quiz]
GO

/****** Object:  View [dbo].[meytal]    Script Date: 16/06/2017 09:21:27 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE VIEW [dbo].[meytal]
AS
SELECT DISTINCT custid, the_top.supid, the_top.orderid, the_top.orderdate
FROM            cust_orders AS org_tbl CROSS apply
                             (SELECT        TOP 1 orderdate, orderid, supid
                               FROM            cust_orders
                               WHERE        custid = org_tbl.custid
                               ORDER BY orderdate DESC) AS the_top

GO
