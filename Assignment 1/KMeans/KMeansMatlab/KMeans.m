addpath("cvs/")
kcluster = readtable("cvs/KCluster.csv");

depth = unique(kcluster.D);

dIndex = uint8(kcluster{:, "D"});
kindex = uint8(kcluster{:,"K"});
x = kcluster{:, "X"};
y = kcluster{:, "Y"};

cluster = readtable("cvs/Cluster.csv");
cDIndex = uint8(cluster{:, "D"});
cKIndex = uint8(cluster{:, "K"});
studentNumber = string(cluster{:, 3});
cX = cluster{:, "X"};
cY = cluster{:, "Y"};

cog = [];
find = 1;
for i = 1:size(dIndex, 1)
    if dIndex(i) == find
        j = size(cog, 1) + 1
        cog(j,1) = x(i);
        cog(j,2) = y(i);
    end
end

cluster = [];
find = 1;
for i = 1:size(cDIndex, 1)
    if cDIndex(i) == find
        j = size(cluster, 1) + 1
        cluster(j,1) = cX(i);
        cluster(j,2) = cY(i);
    end
end

combination = cluster;
colours = string.empty;
for i = 1:size(combination, 1)
    colours(i) = "Yellow";
end

for i = 1:size(cog, 1)
    colours(size(combination, 1) + 1) = "Magenta";
    combination(size(combination, 1) + 1, :) = cog(i, :);
end

for i = 1:size(combination, 1)
   scatter(app.KMeansScatter, combination(i,1), combination(i,2), 36, colours(i),"filled");
end
