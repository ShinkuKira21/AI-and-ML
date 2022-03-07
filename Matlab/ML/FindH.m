data = [0.0, 0.2, 0.27, 0.67, 0.86, 1];
newData = data;
for i = 1:length(data)
    newData(i) = data(i) * -0.1828 + 0.408;
end