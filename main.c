#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*@Author Christian Clark
 *@Date 7/17/25
 *This was a project to see if i could implement a Knn algorithm in C
 */

//struct to hold the data features for wine but also to hold data in general
struct Data {
    float fixedAcid;
    float volAcid;
    float citric;
    float sugar;
    float chlorides;
    float sulfur;
    float density;
};

//struct to represent a single Wine
struct Wine {
    struct Data features;
    float score;
};

//This struct exists so i can sort distances and keep the wine coupled to those distances
struct DistanceIndex{
    float distance;
    struct Wine *wine;
};

//Global Variables
struct Wine *wine;
struct Wine inputWine;
struct Data inputZ;
int k;
struct DistanceIndex *distances;
struct Data *means;
struct Data *deviations;
struct Data *Zscore;
int numWine;

//Finds the means of the dataset we've read
float findMeans() {
    float totFixedAcid = 0, totVolAcid = 0, totCitric = 0, totSugar = 0, totChlorides = 0, totSulfur = 0, totDensity =
            0;
    for (int i = 0; i < numWine; i++) {
        //collects the total of each feature
        totFixedAcid += wine[i].features.fixedAcid;
        totVolAcid += wine[i].features.volAcid;
        totCitric += wine[i].features.citric;
        totSugar += wine[i].features.sugar;
        totChlorides += wine[i].features.chlorides;
        totSulfur += wine[i].features.sulfur;
        totDensity += wine[i].features.density;
    }

    totFixedAcid /= numWine;
    totVolAcid /= numWine;
    totCitric /= numWine;
    totSugar /= numWine;
    totChlorides /= numWine;
    totSulfur /= numWine;
    totDensity /= numWine;

    means->fixedAcid = totFixedAcid;
    means->volAcid = totVolAcid;
    means->citric = totCitric;
    means->sugar = totSugar;
    means->chlorides = totChlorides;
    means->sulfur = totSulfur;
    means->density = totDensity;

    return 0;
}

//Finds the standard deviation of the dataset we've read
//dev = sqrt(add((x - u)^2) / n)
float findDeviations() {
    float SIGMA;
    float total = 0;

    for (int y = 0; y < 7; y++) {
        total = 0;
        for (int i = 0; i < numWine; i++) {
            switch (y) {
                //Fixed Acid
                case 0:
                    SIGMA = wine[i].features.fixedAcid - means->fixedAcid;
                    break;
                case 1:
                    SIGMA = wine[i].features.volAcid - means->volAcid;
                    break;
                case 2:
                    SIGMA = wine[i].features.citric - means->citric;
                    break;
                case 3:
                    SIGMA = wine[i].features.sugar - means->sugar;
                    break;
                case 4:
                    SIGMA = wine[i].features.chlorides - means->chlorides;
                    break;
                case 5:
                    SIGMA = wine[i].features.sulfur - means->sulfur;
                    break;
                case 6:
                    SIGMA = wine[i].features.density - means->density;
                    break;
            }
            total += SIGMA * SIGMA;
        }
        float distance = total / numWine;
        distance = sqrtf(distance);
        switch (y) {
            //Fixed Acid
            case 0:
                deviations->fixedAcid = distance;
                break;
            case 1:
                deviations->volAcid = distance;
                break;
            case 2:
                deviations->citric = distance;
                break;
            case 3:
                deviations->sugar = distance;
                break;
            case 4:
                deviations->chlorides = distance;
                break;
            case 5:
                deviations->sulfur = distance;
                break;
            case 6:
                deviations->density = distance;
                break;
        }
    }
}

//Finds the Zscore of all of the wine and their features
//Z = (x - u) / dev
float findZScore() {
    float Z;

    for (int i = 0; i < numWine; i++) {
        for (int y = 0; y < 7; y++) {
            switch (y) {
                case 0:
                    Z = wine[i].features.fixedAcid - means->fixedAcid;
                    Z = Z / deviations->fixedAcid;
                    Zscore[i].fixedAcid = Z;
                    break;
                case 1:
                    Z = wine[i].features.volAcid - means->volAcid;
                    Z = Z / deviations->volAcid;
                    Zscore[i].volAcid = Z;
                    break;
                case 2:
                    Z = wine[i].features.citric - means->citric;
                    Z = Z / deviations->citric;
                    Zscore[i].citric = Z;
                    break;
                case 3:
                    Z = wine[i].features.sugar - means->sugar;
                    Z = Z / deviations->sugar;
                    Zscore[i].sugar = Z;
                    break;
                case 4:
                    Z = wine[i].features.chlorides - means->chlorides;
                    Z = Z / deviations->chlorides;
                    Zscore[i].chlorides = Z;
                    break;
                case 5:
                    Z = wine[i].features.sulfur - means->sulfur;
                    Z = Z / deviations->sulfur;
                    Zscore[i].sulfur = Z;
                    break;
                case 6:
                    Z = wine[i].features.density - means->density;
                    Z = Z / deviations->density;
                    Zscore[i].density = Z;
                    break;
            }
        }
    }
}

//Finds the Zscore of a single wine and stores it in a passed in Data pointer
float findZScoreSingle(struct Wine input, struct Data *outz) {
    float Z;

    Z = input.features.fixedAcid - means->fixedAcid;
    Z = Z / deviations->fixedAcid;
    outz->fixedAcid = Z;

    Z = input.features.volAcid - means->volAcid;
    Z = Z / deviations->volAcid;
    outz->volAcid = Z;

    Z = input.features.citric - means->citric;
    Z = Z / deviations->citric;
    outz->citric = Z;

    Z = input.features.sugar - means->sugar;
    Z = Z / deviations->sugar;
    outz->sugar = Z;

    Z = input.features.chlorides - means->chlorides;
    Z = Z / deviations->chlorides;
    outz->chlorides = Z;

    Z = input.features.sulfur - means->sulfur;
    Z = Z / deviations->sulfur;
    outz->sulfur = Z;

    Z = input.features.density - means->density;
    Z = Z / deviations->density;
    outz->density = Z;
}

float Distance(struct Data a, struct Data b) {
    float distance = sqrtf((a.fixedAcid - b.fixedAcid) * (a.fixedAcid - b.fixedAcid) + (a.volAcid - b.volAcid) * (a.volAcid - b.volAcid) + (a.citric - b.citric) * (a.citric - b.citric) + (a.sugar - b.sugar) * (a.sugar - b.sugar) + (a.density - b.density) * (a.density - b.density) +(a.chlorides - b.chlorides) * (a.chlorides - b.chlorides) + (a.sulfur - b.sulfur) * (a.sulfur - b.sulfur));
    return distance;
}

//reads a dataset in and initializes some global variables
int initData() {
    FILE *wineData = fopen("./wine.dat", "r");
    if (wineData == NULL) {
        printf("Error opening wine.dat\n");
        exit(1);
    }
    printf("wine.dat loaded\n\n");

    float inScore;
    fscanf(wineData, "%d", &numWine);
    distances = malloc(sizeof(struct DistanceIndex) * numWine);
    wine = (struct Wine *) malloc(sizeof(struct Wine) * numWine);
    means = (struct Data *) malloc(sizeof(struct Data));
    deviations = (struct Data *) malloc(sizeof(struct Data));
    Zscore = (struct Data *) malloc(sizeof(struct Data) * numWine);

    for (int i = 0; i < numWine; i++) {
        fscanf(wineData, "%f %f %f %f %f %f %f %f",
               &wine[i].features.fixedAcid,
               &wine[i].features.volAcid,
               &wine[i].features.citric,
               &wine[i].features.sugar,
               &wine[i].features.chlorides,
               &wine[i].features.sulfur,
               &wine[i].features.density,
               &wine[i].score);
    }

    for (int i = 0; i < numWine; i++) {
        printf("%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",
               wine[i].features.fixedAcid,
               wine[i].features.volAcid,
               wine[i].features.citric,
               wine[i].features.sugar,
               wine[i].features.chlorides,
               wine[i].features.sulfur,
               wine[i].features.density,
               wine[i].score);
    }
    fclose(wineData);
    FILE *inputfile = fopen("./input.txt", "r");
    if (inputfile == NULL) {
        printf("Error opening input file\n");
        exit(1);
    }
    fscanf(inputfile, "%d", &k);
    fscanf(inputfile, "%f %f %f %f %f %f %f",
           &inputWine.features.fixedAcid,
           &inputWine.features.volAcid,
           &inputWine.features.citric,
           &inputWine.features.sugar,
           &inputWine.features.chlorides,
           &inputWine.features.sulfur,
           &inputWine.features.density);

    fclose(inputfile);
    printf("\n");
    printf("k = %d\nInput wine: %f %f %f %f %f %f %f\n",
           k,
           inputWine.features.fixedAcid,
           inputWine.features.volAcid,
           inputWine.features.citric,
           inputWine.features.sugar,
           inputWine.features.chlorides,
           inputWine.features.sulfur,
           inputWine.features.density);
}

//compares the distances between two DistanceIndexes
//To be used with qsort
int CompareDistances(const void *a, const void *b) {
    struct DistanceIndex *ia = (struct DistanceIndex *) a;
    struct DistanceIndex *ib = (struct DistanceIndex *) b;

    if (ia->distance < ib->distance) return -1;
    if (ia->distance > ib->distance) return 1;
    return 0;
}

int main(void) {
    initData();

    findMeans();
    findDeviations();
    findZScore();
    findZScoreSingle(inputWine, &inputZ);

    printf("\nMeans:\n");
    printf("Fixed Acid: %f\n", means->fixedAcid);
    printf("Vol. Acid: %f\n", means->volAcid);
    printf("Citric: %f\n", means->citric);
    printf("Sugar: %f\n", means->sugar);
    printf("Chlorid: %f\n", means->chlorides);
    printf("Sulfur: %f\n", means->sulfur);
    printf("Density: %f\n", means->density);

    printf("\nDeviations:\n");
    printf("Fixed Acid: %f\n", deviations->fixedAcid);
    printf("Vol. Acid: %f\n", deviations->volAcid);
    printf("Citric: %f\n", deviations->citric);
    printf("Sugar: %f\n", deviations->sugar);
    printf("Chlorid: %f\n", deviations->chlorides);
    printf("Sulfur: %f\n", deviations->sulfur);
    printf("Density: %f\n", deviations->density);

    printf("\nZscores\n");
    for (int i = 0; i < numWine; i++) {
        printf("%.2f %.2f %.2f %.2f %.2f %.2f %.2f \n",
               Zscore[i].fixedAcid,
               Zscore[i].volAcid,
               Zscore[i].citric,
               Zscore[i].sugar,
               Zscore[i].chlorides,
               Zscore[i].sulfur,
               Zscore[i].density);
    }

    printf("\nInput Wine's ZScores:\n");
    printf("%.2f %.2f %.2f %.2f %.2f %.2f %.2f \n",
           inputZ.fixedAcid,
           inputZ.volAcid,
           inputZ.citric,
           inputZ.sugar,
           inputZ.chlorides,
           inputZ.sulfur,
           inputZ.density);

    for (int i = 0; i < numWine; i++) {
        distances[i].distance = Distance(inputZ, Zscore[i]);
        distances[i].wine = &wine[i];
    }

    printf("\nDistances:\n");
    for (int i = 0; i < numWine; i++) {
        printf("%.2f\n", distances[i].distance);
    }

    qsort(distances, numWine, sizeof(distances[0]), CompareDistances);

    printf("\nSorted Distances:\n");
    for (int i = 0; i < numWine; i++) {
        printf("%.2f %.2f\n", distances[i].distance, distances[i].wine->score);
    }

    printf("\nEstimated Score:\n");
    float score = 0;
    for (int i = 0; i < k; i++) {
        score += distances[i].wine->score;
    }
    score /= k;
    printf("Score: %.2f\n", score);

    return 0;
}
