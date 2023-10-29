#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double sqrt(double x);

struct DistanceAndIndice {
    double distance;
    size_t index;
};

struct DistanceAndIndice *sort_distances(struct DistanceAndIndice distances[], int size) {
    struct DistanceAndIndice *dist = malloc(sizeof(struct DistanceAndIndice) * size);
    memcpy(dist, distances, sizeof(struct DistanceAndIndice)* size);
    for (size_t step = 0; step < size - 1; ++step) {
        for (size_t i = 0; i < size-step-1; ++i) {
            if (dist[i].distance > dist[i+1].distance) {
                struct DistanceAndIndice temp = dist[i];
                dist[i] = dist[i + 1];
                dist[i+1] = temp;
            }
        }
    }
    return dist;
}

double knearest(double data[10][2], double query, int k) {
    struct DistanceAndIndice distances[10];
    for (size_t i = 0; i < 10; i++) {
        double example = data[i][0];
        struct DistanceAndIndice distance = {};
        distance.index = i;
        distance.distance = example - query;
        // probably have to normalize this
        if (distance.distance < 0) {
            distance.distance *= -1;
        }
        distances[i] = distance;
    }

    struct DistanceAndIndice *sorted = sort_distances(distances, 10);
    double average = 0;
    for (size_t j = 0; j < k-1; j++) {
        average += data[sorted[j].index][1];
    }
    average /= (k-1);
    return average;
}


int main() {
    double data[10][2] = {
       {65.75, 112.99},
       {71.52, 136.49},
       {69.40, 153.03},
       {68.22, 142.34},
       {67.79, 144.30},
       {68.70, 123.30},
       {69.80, 141.49},
       {70.01, 136.46},
       {67.90, 112.37},
       {66.49, 127.45}
    };
    double nearest = knearest(data, 68.50, 3);
    printf("Can I implement K Nearest Neighbours? \n");
    printf("Nearest is: %f \n", nearest);
    return 0;
}
