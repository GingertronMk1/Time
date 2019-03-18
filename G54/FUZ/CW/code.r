library(FuzzyR)

# A FUNCTION TO DRAW A FIS

drawfis <- function(f,n) {
  # Converting the number passed in to a string
  nString <- toString(n);
  if (nchar(nString) == 1) {
    nString <- paste("0", nString, sep="");
  }
  # Drawing the FIS f's membership functions and control surface to a png
  png(filename = paste("membershipFns", nString, ".png", sep="")
     ,width = 4000, height = 4000, units = "px", pointsize = 12
     ,bg = "white",  res = NA
     ,type = c("cairo", "cairo-png", "Xlib", "quartz"));
  par(mfrow=c(2,2));
  plotmf(f, 'input',  1,  main = "Temperature (°C)");
  plotmf(f, 'input',  2,  main = "Headache");
  plotmf(f, 'output', 1,  main = "Urgency");
  gensurf(f);
  # Printing details about the FIS f to a text file
  sink(file = paste("fis", nString, ".txt", sep="")
      ,append = FALSE
      ,type = c("output", "message")
      ,split = FALSE);
  showfis(f);
  showrule(f);
  print(paste("RMSE:", rmsecheck(f)));
  closeAllConnections();
  print(paste("Printed", nString));
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

  f <- addmf(f, 'input', 2, 'none',           'trapmf', c(0,0,1,2));
  f <- addmf(f, 'input', 2, 'mild',           'trapmf', c(0,1,3,4));
  f <- addmf(f, 'input', 2, 'moderate',       'trapmf', c(3,4,6,7));
  f <- addmf(f, 'input', 2, 'severe',         'trapmf', c(6,7,9,10));
  f <- addmf(f, 'input', 2, 'worst possible', 'trapmf', c(8,9,10,10));

  f <- addmf(f, 'output', 1, 'none',      'gaussmf', c(2,0));
  f <- addmf(f, 'output', 1, 'some',      'gaussmf', c(1,3.5));
  f <- addmf(f, 'output', 1, 'medium',    'gaussmf', c(1,5.5));
  f <- addmf(f, 'output', 1, 'priority',  'gaussmf', c(1,7.5));
  f <- addmf(f, 'output', 1, 'emergency', 'gaussmf', c(1,10));

  return(f);
}

rmse <- function(actual, expected) {
  return(sqrt(mean((actual - expected)^2)))
}

values= rbind(
     c(35, 0)
    ,c(35, 1)
    ,c(35, 2)
    ,c(35, 3)
    ,c(35, 4)
    ,c(35, 5)
    ,c(35, 6)
    ,c(35, 7)
    ,c(35, 8)
    ,c(35, 9)
    ,c(35, 10)
    ,c(36, 0)
    ,c(36, 1)
    ,c(36, 2)
    ,c(36, 3)
    ,c(36, 4)
    ,c(36, 5)
    ,c(36, 6)
    ,c(36, 7)
    ,c(36, 8)
    ,c(36, 9)
    ,c(36, 10)
    ,c(37, 0)
    ,c(37, 1)
    ,c(37, 2)
    ,c(37, 3)
    ,c(37, 4)
    ,c(37, 5)
    ,c(37, 6)
    ,c(37, 7)
    ,c(37, 8)
    ,c(37, 9)
    ,c(37, 10)
    ,c(38, 0)
    ,c(38, 1)
    ,c(38, 2)
    ,c(38, 3)
    ,c(38, 4)
    ,c(38, 5)
    ,c(38, 6)
    ,c(38, 7)
    ,c(38, 8)
    ,c(38, 9)
    ,c(38, 10)
    ,c(39, 0)
    ,c(39, 1)
    ,c(39, 2)
    ,c(39, 3)
    ,c(39, 4)
    ,c(39, 5)
    ,c(39, 6)
    ,c(39, 7)
    ,c(39, 8)
    ,c(39, 9)
    ,c(39, 10)
  )

expected= rbind(
     10   # 35, 0
    ,10   # 35, 1
    ,10   # 35, 2
    ,10   # 35, 3
    ,10   # 35, 4
    ,10   # 35, 5
    ,10   # 35, 6
    ,10   # 35, 7
    ,10   # 35, 8
    ,10   # 35, 9
    ,10   # 35, 10
    ,2    # 36, 0
    ,3    # 36, 1
    ,4    # 36, 2
    ,5    # 36, 3
    ,6    # 36, 4
    ,7    # 36, 5
    ,8    # 36, 6
    ,10   # 36, 7
    ,10   # 36, 8
    ,10   # 36, 9
    ,10   # 36, 10
    ,0    # 37, 0
    ,0    # 37, 1
    ,0    # 37, 2
    ,1    # 37, 3
    ,2    # 37, 4
    ,3    # 37, 5
    ,5    # 37, 6
    ,7    # 37, 7
    ,8    # 37, 8
    ,10   # 37, 9
    ,10   # 37, 10
    ,2    # 38, 0
    ,3    # 38, 1
    ,4    # 38, 2
    ,5    # 38, 3
    ,6    # 38, 4
    ,7    # 38, 5
    ,8    # 38, 6
    ,10   # 38, 7
    ,10   # 38, 8
    ,10   # 38, 9
    ,10   # 38, 10
    ,10   # 39, 0
    ,10   # 39, 1
    ,10   # 39, 2
    ,10   # 39, 3
    ,10   # 39, 4
    ,10   # 39, 5
    ,10   # 39, 6
    ,10   # 39, 7
    ,10   # 39, 8
    ,10   # 39, 9
    ,10   # 39, 10
  )

rmsecheck <- function(f) {
  return(rmse(evalfis(values, f), expected));
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

fis7P <- fillFis(newfis("Hospital"
                      ,defuzzMethod = "som"
                      )
               );
fis7 <- addrule(fis7P, rule4);

fis8 <- fillFis(newfis("Hospital"
                      ,defuzzMethod = "lom"
                      )
               );
fis8 <- addrule(fis8, rule4);

fis9 <- fillFis(newfis("Hospital"
                      ,impMethod = "prod"
                      )
               );
fis9 <- addrule(fis9, rule4);

fisGauss <- newfis("Hospital"
               ,impMethod="prod");

fisGauss <- addvar(fisGauss, 'input',   'temperature',  c(35,39));
fisGauss <- addvar(fisGauss, 'input',   'headache',     c(0,10));
fisGauss <- addvar(fisGauss, 'output',  'urgency',      c(0,10));

fisGauss <- addmf(fisGauss, 'input', 1, 'hypothermic',  'gaussmf', c(0.5,35));
fisGauss <- addmf(fisGauss, 'input', 1, 'low',          'gaussmf', c(0.5,36));
fisGauss <- addmf(fisGauss, 'input', 1, 'normal',       'gaussmf', c(0.5,37));
fisGauss <- addmf(fisGauss, 'input', 1, 'high',         'gaussmf', c(0.5,38));
fisGauss <- addmf(fisGauss, 'input', 1, 'hyperthermic', 'gaussmf', c(0.5,39));

fisGauss <- addmf(fisGauss, 'input', 2, 'none',           'gaussmf', c(2,0));
fisGauss <- addmf(fisGauss, 'input', 2, 'mild',           'gaussmf', c(1,4));
fisGauss <- addmf(fisGauss, 'input', 2, 'moderate',       'gaussmf', c(1,6));
fisGauss <- addmf(fisGauss, 'input', 2, 'severe',         'gaussmf', c(1,8));
fisGauss <- addmf(fisGauss, 'input', 2, 'worst possible', 'gaussmf', c(1,10));

fisGauss <- addmf(fisGauss, 'output', 1, 'none',      'gaussmf', c(3,0));
fisGauss <- addmf(fisGauss, 'output', 1, 'some',      'gaussmf', c(1,4));
fisGauss <- addmf(fisGauss, 'output', 1, 'medium',    'gaussmf', c(1,6));
fisGauss <- addmf(fisGauss, 'output', 1, 'priority',  'gaussmf', c(1,8));
fisGauss <- addmf(fisGauss, 'output', 1, 'emergency', 'gaussmf', c(1,10));

rule10_1 <- c(3,1,1,1,1);
rule10_2 <- c(3,3,2,0.5,1);
rule10_3 <- c(3,2,2,0.5,1);
rule10_4 <- c(3,4,3,0.5,1);
rule10_5 <- c(1,5,5,1,2);
rule10_6 <- c(5,5,5,1,2);
rule10_7 <- c(5,0,5,1,1);
rule10_8 <- c(1,0,5,1,1);
rule10_9 <- c(0,5,5,1,1);

rule10 <- rbind(rule10_1
              ,rule10_2
              ,rule10_3
              ,rule10_4
              ,rule10_5
              ,rule10_6
              ,rule10_7
              ,rule10_8
              ,rule10_9
               );

fis10 <- addrule(fisGauss, rule10);
fis11 <- addrule(fisGauss, rule4);

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
drawfis(fis10,10);
drawfis(fis11,11);
#showGUI(fis10);

writefis = fuzzyr.match.fun('writefis');

writefis(fis10);
