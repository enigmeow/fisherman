/*
PlayG    Street    Fisherman    Dock1    Dock2    Dock3    Dock4    R    G    B    Zone
TTC    PG    -68.075    -63.5    -77.5    -90.2    -94.9    24    150    128    2000
        1.826    61.6    47    42.5    31.4                
TTC    LL    -226.697    -233.5    -220.4    -248.5    -247.2    25    144    124    2236
        143.216    161.5    189    189    161.2                
TTC    SS    11.976    4.5    4.4    35.3    35.4    25    144    124    2156
        -632.887    -658.2    -671.5    -672.4    -658.1                
TTC    PP    492.6    512.4    529.8    542.7    530.1    26    142    121    2341
        -78.347    -70    -83.8    -70    -56.1                
DG    PG    66.743    64.3    62.5    45.5    40.6    11    104    75    5000
        11.649    41.7    57.9    59.1    39.8                
DG    OS    134.541    148.2    148.6    120.8    120.4    20    103    77    5318
        -92.765    -83.8    -56    -55.6    -83.8                
DG    MS    200.682    187.3    179.3    170.9    163    15    99    75    5245
        74.533    114.1    114    114.9    113.6                
DG    ES    148.675    135    135.4    163    163.9    16    100    76    5139
        20.076    30    56.8    57.5    28.9                
DD    PG    -12.488    -1.8    -11.6    -23.6    -31.4    27    91    179    1000
        177.631    140    148.5    149.1    141.4                
DD    LL    373.538    361.3    353.7    346.2    338.8    35    74    133    1330
        119.635    89.9    88.2    88.2    89.9                
DD    SS    -412.765    -394.9    -412.4    -395.3    -378    37    78    134    1236
        -251.685    -243.1    -229.4    -208.1    -228.7                
DD    BB    350.313    368.1    370.5    389.4    392    41    76    140    1129
        -347.931    -339.9    -363.7    -364    -340                
MM    PG    -57.688    -15.6    0.1    0.2    15    11    136    154    4000
        -58.913    -19.9    -36    -5.9    -19.8                
MM    TT    748.23    725.3    705.1    705.4    724.5    29    106    150    4345
        -14.529    -26.2    -26.5    -3.2    -3.1                
MM    AA    Josh    Josh    Josh    Josh    Josh    Josh    Josh    Josh    Josh
        Josh    Josh    Josh    Josh    Josh    Josh    Josh    Josh    Josh
MM    BB    -247.989    -225.3    -205    -205.7    -224.7    28    105    146    4240
        249.021    261.4    261.6    238.2    238.4                
TB    PG    -119.603    -66.4    -46    -54.4    -70.4                3000
        -34.77    -33.2    -32.3    -15.3    -16.2                
TB    PP    23.493    35    54.2    54.2    35    Josh    Josh    Josh    3329
        93.497    105    105.5    75.4    75    Josh    Josh    Josh    
TB    WW    Josh    Josh    Josh    Josh    Josh    Josh    Josh    Josh    Josh
        Josh    Josh    Josh    Josh    Josh    Josh    Josh    Josh    Josh
TB    SS    359.276    340    322.6    340    356.7    Josh    Josh    Josh    3236
        458.392    462.9    479.9    479.2    480    Josh    Josh    Josh    
DDL    PG    150.404    169.6    172.8    151.1    145.2    55    97    113    9000
        -14.997    15.9    -6.8    -11.4    6.9                
DDL    PP    258.908    248.7    232.7    227.9    239.6    55    102    118    9255
        -352.273    -365.6    -361    -344.7    -330.6                
DDL    LL    117.084    106.8    115.9    125.8    132.7    57    103    119    9153
      -150.913    -197.4    -199.6    -198.1    -191.6                
*/



struct FishingSpots {
  const char *district_;
  const char *pond_;
  double fisherx_, fishery_;
  double pondx1_, pondy1_;
  double pondx2_, pondy2_;
  double pondx3_, pondy3_;
  double pondx4_, pondy4_;
  int r_, g_, b_;
  int zone_;
  int tol_;
} spots_[] = {
  {"Toontown Central", "Play ground", -68.075, 1.826, -63.5, 61.6, -77.5, 47, -90.2, 42.5, -94.9, 31.4, 24, 150, 128, 2000, 10}, 
  {"Toontown Central", "Loopy Lane", -226.697, 143.216, -233.5, 161.5, -220.4, 189, -248.5, 189, -247.2, 161.2, 25, 144, 124, 2236, 10}, 
  {"Toontown Central", "Silly Street", 11.976, -632.887, 4.5, -658.2, 4.4, -671.5, 35.3, -672.4, 35.4, -658.1, 25, 144, 124, 2156, 10}, 
  {"Toontown Central", "Punchline Place", 492.6, -78.347, 512.4, -70, 529.8, -83.8, 542.7, -70, 530.1, -56.1, 26, 142, 121, 2341, 10}, 
  {"Daisy Gardens", "Play ground", 66.743, 11.649, 64.3, 57.9, 62.5, 57.9, 45.5, 59.1, 40.6, 39.8, 11, 104, 75, 5000, 10}, 
  {"Daisy Gardens", "OS", 134.541, -92.765, 148.2, -83.8, 148.6, -56, 120.8, -55.6, 120.4, -83.8, 20, 103, 77, 5318, 10}, 
  {"Daisy Gardens", "MS", 200.682, 74.533, 187.3, 114.1, 179.3, 114, 170.9, 114.9, 163, 113.6, 15, 99, 75, 5245, 10}, 
  {"Daisy Gardens", "ES", 148.675, 20.076, 135, 30, 135.4, 56.8, 163, 57.5, 163.9, 28.9, 16, 100, 76, 5139, 10}, 
  {"Donalds Dock", "Play ground", -12.488, 177.631, -1.8, 140, -11.6, 148.5, -23.6, 149.1, -31.4, 141.4, 27, 91, 179, 1000, 10}, 
  {"Donalds Dock", "LL", 373.538, 119.635, 361.3, 89.9, 353.7, 88.2, 346.2, 88.2, 338.8, 89.9, 35, 74, 133, 1330, 10}, 
  {"Donalds Dock", "SS", -412.765, -251.685, -394.9, -243.1, -412.4, -229.4, -395.3, -208.1, -378, -228.7, 37, 78, 134, 1236, 10}, 
  {"Donalds Dock", "BB", 350.313, -347.931, 368.1, -339.9, 370.5, -363.7, 389.4, -364, 392, -340, 41, 76, 140, 1129, 10}, 
  {"Minnies Melody Land", "Play ground", -57.688, -58.913, -15.6, -19.9, 0.1, -36, 0.2, -5.9, 15, -19.8, 11, 136, 154, 4000, 10}, 
  {"Minnies Melody Land", "Tenor Terrace", 748.23, -14.529, 725.3, -26.2, 705.1, -26.5, 705.4, -3.2, 724.5, -3.1, 29, 106, 150, 4345, 10}, 
  {"Minnies Melody Land", "Alto Avanue", -613.201, -90.088, -590.7,-78.9, -570.1,-78.6, 0,0,0,0, 31, 106, 148, 0, 10}, 
  {"Minnies Melody Land", "Baritone Boulevard", -247.989, 249.021, -225.3, 261.4, -205, 261.6, -205.7, 238.2, -224.7, 238.4, 28, 105, 146, 4240, 10}, 
  {"The Brrgs", "Play ground", -119.603, -34.77, -66.4, -33.2, -46, -32.3, -54.4, -15.3,  -70.4, -16.2, 70, 130, 148, 3000, 6},
  {"The Brrgs", "PP", 23.493, 93.497, 35, 105, 54.2, 105.5, 54.2, 75.4, 35, 75, 21, 139, 141, 3329, 10}, 
  {"The Brrgs", "WW", 488,  36,  455.4, 15.7, 464, 15.6, 465.1 , 45.3, 455.6 , 45.3, 21, 139, 141, 0, 10},
  {"The Brrgs", "SS", 359.276, 458.392, 340, 462.9, 322.6, 479.9, 340, 479.2, 356.7, 480, 21, 139, 141, 3236, 10}, 
  {"Donalds Dreamland", "Play ground", 150.404, -14.997, 169.6, 15.9, 172.8, -6.8, 151.1, -11.4, 145.2, 6.9, 55, 97, 113, 9000, 10}, 
  {"Donalds Dreamland", "PP", 258.908, -352.273, 248.7, -365.6, 232.7, -361, 227.9, -344.7, 239.6, -330.6, 55, 102, 118, 9255, 10}, 
  {"Donalds Dreamland", "LL", 117.084, -150.913, 106.8, -197.4, 115.9, -199.6, 125.8, -198.1, 132.7, -191.6, 57, 103, 119, 9153, 10}
};