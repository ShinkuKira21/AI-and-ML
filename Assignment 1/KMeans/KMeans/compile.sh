echo "Author(s): Edward Patch - Compiling with G++"
echo "Run ./KMeans.out to execute the KMeans cluster program."
g++ main.cpp ClusterTools/clustergen.cpp ClusterTools/kmeans.cpp -o KMeans.out -Wall -Werror -fsanitize=leak

if [ $? -eq 0 ]; then
    echo "Starting KMeans Cluster..."
    ./KMeans.out
fi