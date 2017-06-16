USE [quiz]
GO

/****** Object:  View [dbo].[meytal_partition]    Script Date: 16/06/2017 09:15:39 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE VIEW [dbo].[meytal_partition]
AS
WITH cte AS
(
   SELECT *,
         ROW_NUMBER() OVER (PARTITION BY custid ORDER BY orderdate DESC) AS rn
   FROM cust_orders
)
SELECT custid,supid,orderid,orderdate
FROM cte
WHERE rn = 1

GO
