require("ggplot2")
require("tidyr")
require("scales")

setwd("/Users/Jack/Git/Time/FIV/")

music <- read.csv("Music.csv",header=TRUE,quote="\"") # read the music csv file

music$notes <- NULL # the notes column is not especially useful to us

music <- subset(music,year!="unknown")   # filtering out those rows with no year


for (i in c(4,16:ncol(music))) {
  music[,i] <- as.numeric(as.character(music[,i]))
}

music <- subset(music[order(music$year, music$type),], type!="NA")



# YEAR AGAINST SCORE

yearScoreData <- subset(music, select=c(year,score), type=="song")    # Creating a subset of music with only year and score for songs

yearScoreData$year <- sapply(yearScoreData$year, function(x) (round(x/5)*5))    # Rounding the years to the nearest 5

yearScorePlot <- ggplot(yearScoreData, aes(x=year, y=score, group=year)) +
                 geom_boxplot(outlier.color="black", outlier.shape=16, outlier.size=0.2) +
                 labs(x="First Year", y="Score")

ggsave(yearScorePlot,file="Images/yearScore.png")


# POSITION IN TOP 100 AGAINST SCORE

scoreSellData <- subset(music, songyear_pos>0)          # Only songs in the top 100 of the year

scoreSellPlot <- ggplot(scoreSellData,aes(x=score,y=songyear_pos)) +
                 geom_point(size=1) +
                 coord_cartesian(ylim=c(0,100)) +
                 scale_y_reverse() +
                 geom_smooth(method='lm',formula=y~x) +
                 labs(x="Score",y="Position in Top 100")

ggsave(scoreSellPlot,file="Images/scoreSell.png")


# NUMBERS OF SINGLES AND ALBUMS AGAINST YEAR

singlesAlbumsData <- data.frame(table(music$year, music$type))

names(singlesAlbumsData) <- c("year", "type", "count")

singlesAlbumsData <- spread(singlesAlbumsData, type, count)

singlesAlbumsPlot <- ggplot(singlesAlbumsData, aes(x=year, group=1)) +
                     scale_x_discrete(breaks=seq(1900,2020, by=25)) +
                     geom_line(aes(y=album,color="Album")) +
                     geom_line(aes(y=song,color="Song")) +
                     labs(x="Year", y="Count", color="Legend\n")

ggsave(singlesAlbumsPlot,file="Images/singlesAlbums.png")

# TOP SONG OF YEAR VS TOP OF DECADE (THIS ISN'T VERY GOOD)

yearDecadeData <- subset(music, songdecade_pos>0)

topSellPlot <- ggplot(subset(music, songdecade_pos==1), aes(x=year, y=songyear_pos)) +
                  geom_point(size=1)

yearDecadePlot <- ggplot(yearDecadeData, aes(x=songyear_pos, y=songdecade_pos)) +
                  coord_cartesian(ylim=c(0,100)) +
                  geom_point(size=1) +
                  scale_x_reverse() +
                  scale_y_reverse() +
                  geom_smooth(method='lm',formula=y~x)

yearDecadePlot2 <- ggplot(subset(yearDecadeData, songdecade_pos>0), aes(x=year, y=songyear_pos)) +
                   scale_y_reverse() +
                   geom_point(size=1)

ggsave(yearDecadePlot, file="Images/yearDecade.png")
ggsave(yearDecadePlot2, file="Images/yearDecade2.png")
ggsave(topSellPlot, file="Images/topSell.png")

# TOP-100 SONGS VS TOP-100 ALBUMS

songAlbumData <- subset(music, select=c(artist, songyear_pos, albumyear_pos))   # Subset of music with only artists, and year positions

songAlbumData <- songAlbumData[order(songAlbumData$artist),]    # Sort by artist

songAlbumData$songyear_pos <- as.numeric(as.character(sapply(songAlbumData$songyear_pos, function(x) (if (is.na(x)){0}else{1}))))   # Transform to binary
songAlbumData$albumyear_pos <- as.numeric(as.character(sapply(songAlbumData$albumyear_pos, function(x) (if (is.na(x)){0}else{1})))) # Effectively boolean (WAS THIS ON CHART)


songAlbumData <- aggregate(. ~ artist, songAlbumData, sum)      # Aggregating to get counts

songAlbumData <- songAlbumData[order(-songAlbumData$songyear_pos),]   # Sorting wrt songyear_pos
songAlbumData <- head(songAlbumData, 25)                              # Taking the top 25

songAlbumPlot <- ggplot(songAlbumData, aes(x=reorder(artist,songyear_pos), group=1)) +
                 geom_bar(aes(y=songyear_pos, color="Songs"), stat="identity", alpha=0.5) +
                 geom_bar(aes(y=albumyear_pos, color="Albums"), stat="identity", alpha=0.5) +
                 coord_flip() +
                 labs(y="Number of Top 100 Year spots", x="Artist Name", color="")  # The x and y-axes are swapped


ggsave(songAlbumPlot, file="Images/songAlbum.png")

# RATINGS OF ALBUMS AGAINST SONGS AGAINST YEARS

songRates <- subset(music, select=c(year, type, score), type=="song")     # Just songs
albumRates <- subset(music, select=c(year, type, score), type=="album")   # Just albums

songRates <- aggregate(. ~ year, songRates, mean)           # Mean scores for songs
albumRates <- aggregate(. ~ year, albumRates, mean)         # Mean scores for albums

albumRates$type <- sapply(albumRates$type, function(x) ("album"))   # The above fn turns the type column into a number
songRates$type <- sapply(songRates$type, function(x) ("song"))      # The type hasn't changed so we can reinstate it thus

songAlbumRatesData <- rbind(albumRates, songRates)                  # Vertical join

songAlbumRatesPlot <- ggplot(songAlbumRatesData, aes(x=year, y=score, color=type)) +
                      geom_line() +
                      labs(x="Year", y="Mean Score", color="Legend\n")

ggsave(songAlbumRatesPlot, file="Images/songAlbumRates.png")
