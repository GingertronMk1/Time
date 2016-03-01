Return all the information from Artist and CD where the artID records are the same for both tables
SELECT * FROM Artist, CD WHERE(Artist.artID = CD.artID)

Find a list of the titles of all CDs by Muse
SELECT cdName FROM CD WHERE(CD.artID = 1);

Use a subquery to find a list of CDs that have the same genre as 'The Resistance'
SELECT cdName FROM CD WHERE(cdGenre = "Rock")

Use IN to find a list of the titles of albums that are the same price as any 'Pop' album
SELECT cdName FROM CD WHERE cdPrice = ALL ( SELECT cdPrice FROM CD WHERE cdGenre = "Pop")

Use ANY to find the titles of CDs that cost more than at least one other CD
SELECT cdName FROM CD WHERE cdPrice > ANY (SELECT cdPrice FROM CD);

Use ALL to find a list of CD titles that cost more or the same as all other CDs
SELECT cdName FROM CD WHERE cdPrice >= ALL (SELECT cdPrice FROM CD);

Use EXISTS to find a list of Artists who produced an 'Electronica' CD
SELECT artName FROM Artist WHERE artID = (SELECT artID FROM CD WHERE cdGenre = "Electronica");

Find the names of Artists who have albums cheaper than £10
SELECT artName FROM Artist WHERE artID = ANY (SELECT artID FROM CD WHERE cdPrice < 10.00);

Find names of CDs produced by those Artists who have a single word as their name
SELECT cdName FROM CD WHERE artID = ANY (SELECT artID FROM Artist WHERE artName NOT LIKE "% %");

Find all information about CDs that are cheaper than others in the 'Rock' and 'Pop' categories only
SELECT * FROM CD WHERE cdPrice < ANY (SELECT cdPrice FROM CD WHERE cdGenre = "ROCK" OR "POP") AND cdGenre = "Rock" OR "POP";
