addpath("cvs/")
dfs = readtable("cvs/DFS.csv");
app.depth = uint8(dfs{:, "D"}); % maybe delete this depth
x = dfs{:, "X"};
y = dfs{:, "Y"};

% default
app.SliderLabel.Text = "Depth";

app.Slider.Value = 0;
app.Slider.Limits = [0 size(app.depth, 1)-1];
app.Slider.MajorTicks = 0:size(app.depth, 1)-1;

for i = 1:size(app.depth, 1)
    app.colours(i, :) = [0.18, 0.67, 0.59]
end