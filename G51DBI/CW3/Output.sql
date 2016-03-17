Output 1:   Titles and prices of CDs, price hi-lo
SELECT cdName, cdPrice 
FROM CD 
ORDER BY cdPrice DESC;

Output 2:   Titles and prices of CDs, price lo-hi
SELECT cdName, cdPrice 
FROM CD 
ORDER BY cdPrice ASC;

Output 3:   Titles, genres, and prices of CDs, genre alphabetically then price hi-lo
SELECT cdName, cdGenre, cdPrice 
FROM CD 
ORDER BY cdGenre ASC, cdPrice DESC;

Output 4:   Lowest price of any CD
SELECT MIN(cdPrice) 
FROM CD;

Output 5:   Number of CDs costing 11.99
SELECT COUNT(cdPrice) 
FROM CD 
WHERE cdPrice = 11.99;

Output 6:   Title of most expensive rock CD(s)
SELECT cdName, MAX(cdPrice) 
FROM CD 
WHERE cdGenre = "Rock";

Output 7:   Number of genres in CD table
SELECT COUNT(DISTINCT cdGenre) 
FROM CD;

Output 8:   All information about cheapest CDs
SELECT *, MIN(cdPrice) 
FROM CD;

Output 9:   List of artist names, number of CDs they produced, and average CD price, only for artists with >1 CD
SELECT CD.artID, Artist.artName, AVG(cdPrice), COUNT(*) AS Count 
FROM CD INNER JOIN Artist 
ON CD.artID=Artist.artID 
GROUP BY artID 
HAVING Count > 1;

Output 10:  List of artist names, number of CDs they produced, and average CD price, no Electronica
SELECT CD.artID, Artist.artName, CD.cdGenre, AVG(cdPrice), COUNT(*) AS Count 
FROM CD INNER JOIN Artist 
ON CD.artID=Artist.artID 
GROUP BY artID HAVING CD.cdGenre <> "Electronica";
