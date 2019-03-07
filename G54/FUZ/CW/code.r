library(FuzzyR)

# A FUNCTION TO DRAW A FIS

drawfis <- function(f,n) {
  # Converting the number passed in to a string
  nString <- toString(n);
  # Drawing the FIS f's surface to a png
  png(filename = paste("surface", nString, ".png", sep=""),
      width = 1000, height = 1000, units = "px", pointsize = 12,
      bg = "white",  res = NA,
      type = c("cairo", "cairo-png", "Xlib", "quartz"));
  gensurf(f);
  # Drawing the FIS f's membership functions to a png
  png(filename = paste("membershipFns", nString, ".png", sep="")
     ,width = 1000, height = 1500, units = "px", pointsize = 12
     ,bg = "white",  res = NA
     ,type = c("cairo", "cairo-png", "Xlib", "quartz"));
  par(mfrow=c(3,1));
  plotmf(f, 'input',  1,  main = "Temperature (°C)");
  plotmf(f, 'input',  2,  main = "Headache");
  plotmf(f, 'output', 1,  main = "Urgency");
  # Writing the FIS f's ruleset to a txt file
  sink(file = paste("rules", nString, ".txt", sep="")
      ,append = FALSE
      ,type = c("output", "message")
      ,split = FALSE);
  showrule(f);
  sink(file = paste("fis", nString, ".txt", sep="")
      ,append = FALSE
      ,type = c("output", "message")
      ,split = FALSE);
  showfis(f);
  closeAllConnections();
}

fillFis <- function(f) {
  f <- addvar(f, 'input',   'temperature',  c(35,39));
  f <- addvar(f, 'input',   'headache',     c(0,10));
  f <- addvar(f, 'output',  'urgency',      c(0,10));

# Hypothermia is below 35 degrees C. [www.nhs.uk/conditions/hypothermia/, 2019-02-21]
# The same source states that a normal body temperature is 37 degrees C.
# They do not have a source on hyperthermia, however it can be reasoned to be the same difference applied positively.
# Therefore we can assume hyperthermia to set in at a body temperature of 39 degrees C.
  f <- addmf(f, 'input', 1, 'hypothermic',  'gaussmf', c(0.5,35));
  f <- addmf(f, 'input', 1, 'low',          'gaussmf', c(0.5,36));
  f <- addmf(f, 'input', 1, 'normal',       'gaussmf', c(0.5,37));
  f <- addmf(f, 'input', 1, 'high',         'gaussmf', c(0.5,38));
  f <- addmf(f, 'input', 1, 'hyperthermic', 'gaussmf', c(0.5,39));

  f <- addmf(f, 'input', 2, 'none',         'trapmf', c(0,0,2,3));
  f <- addmf(f, 'input', 2, 'mild',         'trapmf', c(2,3,4,5));
  f <- addmf(f, 'input', 2, 'moderate',     'trapmf', c(4,5,6,7));
  f <- addmf(f, 'input', 2, 'distressing',  'trapmf', c(6,7,8,9));
  f <- addmf(f, 'input', 2, 'unbearable',   'trapmf', c(8,9,10,10));

  f <- addmf(f, 'output', 1, 'none',      'gaussmf', c(2,0));
  f <- addmf(f, 'output', 1, 'some',      'gaussmf', c(1,3.5));
  f <- addmf(f, 'output', 1, 'medium',    'gaussmf', c(1,5.5));
  f <- addmf(f, 'output', 1, 'priority',  'gaussmf', c(1,7.5));
  f <- addmf(f, 'output', 1, 'emergency', 'gaussmf', c(1,10));

  return(f);
}

# SETTING UP A BASE FIS FROM WHICH THE OPTIONS WILL BE CREATED

fis <- newfis("Hospital");
fis <- fillFis(fis);

# CREATING AND COMPARING FISs

# FIS 1 - ONLY CONSIDERING TEMPERATURE

# RULE SET
# 1. temperature == hypothermic   => urgency = emergency
# 2. temperature == hyperthermic  => urgency = emergency
# 3. temperature == normal        => urgency = none

fis1 <- fis;

rule1_1 <- c(1,0,5,1,1);
rule1_2 <- c(3,0,1,1,1);
rule1_3 <- c(5,0,5,1,1);

rule1 <- rbind(rule1_1, rule1_2, rule1_3);

fis1 <- addrule(fis1, rule1);

# FIS 2 - ONLY CONSIDERING HEADACHE

# RULE SET
# 1. headache == none         => urgency = none
# 2. headache == mild         => urgency = some
# 3. headache == moderate     => urgency = medium
# 4. headache == distressing  => urgency = priority
# 5. headache == unbearable   => urgency = emergency


fis2 <- fis

rule2_1 <- c(0,1,1,1,1);
rule2_2 <- c(0,2,2,1,1);
rule2_3 <- c(0,3,3,1,1);
rule2_4 <- c(0,4,4,1,1);
rule2_5 <- c(0,5,5,1,1);

rule2 <- rbind(rule2_1
              ,rule2_2
              ,rule2_3
              ,rule2_4
              ,rule2_5);

fis2 <- addrule(fis2, rule2);

# FIS 3 - A NÄIVE COMBINATION OF FIS 1 + FIS 2

fis3 <- fis

fis3 <- addrule(fis3, rule1);
fis3 <- addrule(fis3, rule2);

# FIS 4 - SLIGHTLY MORE REALISTIC

# RULE SET
# 1. temp == normal       && headache == none         => urgency = none
# 2. temp == normal       && headache == moderate     => urgency = some
# 3. temp == normal       && headache == mild         => urgency = some
# 4. temp == normal       && headache == distressing  => urgency = medium
# 5. temp == hypothermic  || headache == unbearable   => urgency = emergency
# 6. temp == hyperthermic || headache == unbearable   => urgency = emergency

fis4 <- fis

rule4_1 <- c(3,1,1,1,1);
rule4_2 <- c(3,3,2,1,1);
rule4_3 <- c(3,2,2,1,1);
rule4_4 <- c(3,4,3,1,1);
rule4_5 <- c(1,5,5,1,2);
rule4_6 <- c(5,5,5,1,2);

rule4 <- rbind(rule4_1
              ,rule4_2
              ,rule4_3
              ,rule4_4
              ,rule4_5
              ,rule4_6
               );

fis4 <- addrule(fis4, rule4);

# FIS' 5-8 - AS FIS 4 BUT DIFFERENT DEFUZZ METHODS

fis5 <- fillFis(newfis("Hospital"
                      ,defuzzMethod = "bisector"
                      )
               );
fis5 <- addrule(fis5, rule4);

fis6 <- fillFis(newfis("Hospital"
                      ,defuzzMethod = "mom"
                      )
               );
fis6 <- addrule(fis6, rule4);

fis7 <- fillFis(newfis("Hospital"
                      ,defuzzMethod = "som"
                      )
               );
fis7 <- addrule(fis7, rule4);

fis8 <- fillFis(newfis("Hospital"
                      ,defuzzMethod = "lom"
                      )
               );
fis8 <- addrule(fis8, rule4);

fis9 <- fillFis(newfis("Hospital"
                      ,fisType="sugeno"
                      )
               );
fis9 <- addrule(fis9, rule4);

#DRAWING THE FISs

drawfis(fis1,1);
drawfis(fis2,2);
drawfis(fis3,3);
drawfis(fis4,4);
drawfis(fis5,5);
drawfis(fis6,6);
drawfis(fis7,7);
drawfis(fis8,8);
drawfis(fis9,9);
