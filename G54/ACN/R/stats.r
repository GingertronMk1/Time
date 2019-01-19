require("ggplot2")

setwd("~/Git/Time/ACN/ONEReports/Try_3_2/")

filelist <- list.files(pattern = ".*.txt")

createDF <- function(x) {
  stats <- read.delim(x, header=FALSE, sep=":", dec=".")
  stats <- t(stats)
  colnames(stats) = stats[1,]
  stats = stats[-1,]
  for (i in 2:20) {
    stats[i] <- as.numeric(stats[i])
  }
  stats <- data.frame(t(stats))
}

statss <- lapply(filelist, createDF)
statss <- Reduce(function(x,y) merge(x,y,all=T), statss)
statss <- subset(statss, message_size!=5.5)

for(i in 2:20) {
  statss[,i] <- as.numeric(as.character(statss[,i]))
}

delivprobplot <- ggplot(statss, aes(x=message_size, y=delivery_prob, color=router)) +
                 geom_point() +
                 geom_line() +
                 facet_grid(no_hosts ~ .) +
                 labs(x="Message Size (MB)", y="Delivery Probability", color="Legend\n")

ggsave(delivprobplot, file="Images/delivprobplot.png")

latencyplot <- ggplot(statss, aes(x=message_size, y=latency_avg, color=router)) +
               geom_point() +
               geom_line() +
               facet_grid(no_hosts ~ .) +
               labs(x="Message Size (MB)", y="Average Latency", color="Legend\n")

ggsave(latencyplot, file="Images/latencyplot.png")

hopcountplot <- ggplot(statss, aes(x=message_size, y=hopcount_avg, color=router)) +
                geom_point() +
                geom_line() +
                facet_grid(no_hosts ~ .) +
                labs(x="Message Size (MB)", y="Average Hop Count", color="Legend\n")

ggsave(hopcountplot, file="Images/hopcountplot.png")

buffertimeplot <- ggplot(statss, aes(x=message_size, y=buffertime_avg, color=router)) +
                  geom_point() +
                  geom_line() +
                  facet_grid(no_hosts ~ .) +
                  labs(x="Message Size (MB)", y="Average Buffer Time", color="Legend\n")

ggsave(buffertimeplot, file="Images/buffertimeplot.png")

overheadplot <- ggplot(statss, aes(x=message_size, y=overhead_ratio, color=router)) +
                geom_point() +
                geom_line() +
                facet_grid(no_hosts ~ .) +
                labs(x="Message Size (MB)", y="Average Overhead", color="Legend\n")

ggsave(overheadplot, file="Images/overheadplot.png")

droppedplot <- ggplot(statss, aes(x=message_size, y=dropped, color=router)) +
                geom_point() +
                geom_line() +
                facet_grid(no_hosts ~ .) +
                labs(x="Message Size (MB)", y="Number of Messages Dropped", color="Legend\n")

ggsave(droppedplot, file="Images/droppedplot.png")

startedplot <- ggplot(statss, aes(x=message_size, y=started, color=router)) +
                geom_point() +
                geom_line() +
                facet_grid(no_hosts ~ .) +
                labs(x="Message Size (MB)", y="Number of Messages started", color="Legend\n")

ggsave(startedplot, file="Images/startedplot.png")
