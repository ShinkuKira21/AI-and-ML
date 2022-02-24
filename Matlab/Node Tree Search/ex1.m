map = importdata('m1.txt');

text = []
for i = 1:size(map, 1)
    for j = 1:size(map, 2)
        word = char(map(i));
        text(size(map, 2) * i + j) = word(j)
    end
end

text