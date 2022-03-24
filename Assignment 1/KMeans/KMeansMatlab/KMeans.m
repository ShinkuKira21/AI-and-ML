kcluster = readtable("cvs/KCluster.csv");

depth = unique(kcluster.D);

dIndex = kcluster{:, "D"};
kindex = kcluster{:,"K"};
x = kcluster{:, "X"};
y = kcluster{:, "Y"};

cluster = readtable("cvs/Cluster.csv");
cDIndex = cluster{:, "D"};
cKIndex = cluster{:, "K"};
studentNumber = string(cluster{:, 3});
cX = cluster{:, "X"};
cY = cluster{:, "Y"};