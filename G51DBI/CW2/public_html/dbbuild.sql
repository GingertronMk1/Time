CREATE TABLE Artist (
    artID INT NOT NULL,
    artName VARCHAR(255) NOT NULL,
    CONSTRAINT pk_artist PRIMARY KEY (artID),
    CONSTRAINT ck_artist UNIQUE (artName)
);

CREATE TABLE CD (
    cdID INT NOT NULL,
    artID INT NOT NULL,
    cdName VARCHAR(255) NOT NULL,
    cdPrice DOUBLE NOT NULL,
    cdGenre VARCHAR(255) NOT NULL,
    cdTracks INT NOT NULL,
    CONSTRAINT pk_cd PRIMARY KEY (cdID),
    CONSTRAINT fk_cd_art FOREIGN KEY (artID) REFERENCES Artist (artID),
);

CREATE TABLE Track (
    trackID INT NOT NULL,
    cdID INT NOT NULL,
    trackTitle VARCHAR(255) NOT NULL,
    trackLength DOUBLE NOT NULL,
    CONSTRAINT pk_track PRIMARY KEY (trackID),
    CONSTRAINT fk_track_cd FOREIGN KEY (cdID REFERENCES CD (cdID),
);

INSERT INTO Artist (artName) VALUES ("");

SELECT artID FROM Artist WHERE artName = "";

INSERT INTO CD (artID, cdName, cdPrice, cdGenre) VALUES (1, "", 9.99, "");
