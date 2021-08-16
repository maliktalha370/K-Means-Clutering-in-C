#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int count=0;

//K mean function
kmean(int count , float datax[], float datay[], float datax_org[], float datay_org[])
{
    char *filename = "output.txt";

    int cluster[count], k, l=0, i, flag=0, c0_index =0, c1_index =0, c2_index =0, c3_index =0, c4_index =0;
    float dist = 0;
    float tempx=0, tempy=0, tempx1=0, tempy1=0,
            tempx2=0, tempy2=0, tempx3=0, tempy3=0, tempx4=0, tempy4=0;

    printf("the value of k : 5\n\n");
    k=5;
    float mean[k][2], prev_mean[k][2];
    FILE *fp = fopen(filename, "w");

    // First Cluster centroids
    mean[0][0] = -0.357;
    mean[0][1] = -0.253;

    // Second Cluster centroids
    mean[1][0] = -0.055;
    mean[1][1] = 4.392;

    // Third Cluster centroids
    mean[2][0] = 2.674;
    mean[2][1] = -0.001;

    // Fourth Cluster centroids
    mean[3][0] = 1.044;
    mean[3][1] = -1.251;

    // Fifth Cluster centroids
    mean[4][0] = -1.495;
    mean[4][1] = -0.090;

    int c0= 0, c1= 0, c2= 0, c3= 0, c4 = 0;

    //loop for preparing the cluster
    while(!flag)
    {
        //using Euclidean distance
        c0= 0, c1= 0, c2= 0, c3= 0, c4 = 0;
        for(i=0;i<count;i++)
        {
            c0 = sqrt((pow(mean[0][0]-datax[i],2))+(pow(mean[0][1]-datay[i],2)));
            c1 = sqrt((pow(mean[1][0]-datax[i],2))+(pow(mean[1][1]-datay[i],2)));
            c2 = sqrt((pow(mean[2][0]-datax[i],2))+(pow(mean[2][1]-datay[i],2)));
            c3 = sqrt((pow(mean[3][0]-datax[i],2))+(pow(mean[3][1]-datay[i],2)));
            c4 = sqrt((pow(mean[4][0]-datax[i],2))+(pow(mean[4][1]-datay[i],2)));
            int c;

            int array[5] = {c0, c1, c2, c3, c4}, location = 0;

            for(c = 0; c < k;c++)
                if (array[c] < array[location])
                    location = c;
            cluster[i] = location;
        }



        //prev_mean is used for stopping the loop when previous and current mean are equal
        prev_mean[0][0]=mean[0][0];
        prev_mean[0][1]=mean[0][1];
        prev_mean[1][0]=mean[1][0];
        prev_mean[1][1]=mean[1][1];
        prev_mean[2][0]=mean[2][0];
        prev_mean[2][1]=mean[2][1];
        prev_mean[3][0]=mean[3][0];
        prev_mean[3][1]=mean[3][1];
        prev_mean[4][0]=mean[4][0];
        prev_mean[4][1]=mean[4][1];

        tempx=tempy=tempx1=tempy1=tempx2=tempy2=tempx3=tempy3=tempx4=tempy4=0;
        c0_index = 0, c1_index =0, c2_index =0, c3_index =0, c4_index =0;
        // Expectation step
        //for Euclidean distance measure
        for(i=0;i<count;i++)
        {
            if(cluster[i]==0)
            {
                tempx += datax[i];      //tempx, tempy is used to calculate the centroid of cluster 1
                tempy += datay[i];
                c0_index++;                    //to get the number of data points in cluster 0
            }
            else if(cluster[i]==1)
            {
                tempx1 += datax[i];     //tempx1, tempy1 is used to calculate the centroid of cluster2
                tempy1 += datay[i];
                c1_index++;
            }
            else if(cluster[i]==2)
            {
                tempx2 += datax[i];     //tempx2, tempy2 is used to calculate the centroid of cluster3
                tempy2 += datay[i];
                c2_index++;
            }
            else if(cluster[i]==3)
            {
                tempx3 += datax[i];     //tempx3, tempy3 is used to calculate the centroid of cluster4
                tempy3 += datay[i];
                c3_index++;
            }
            else if(cluster[i]==4)
            {
                tempx4 += datax[i];     //tempx4, tempy4 is used to calculate the centroid of cluster5
                tempy4 += datay[i];
                c4_index++;
            }
        }

        // Maximization step
        //new centroid calculation for both the clusters
        mean[0][0] = tempx/c0_index;
        mean[0][1] = tempy/c0_index;

        mean[1][0] = tempx1/c1_index;
        mean[1][1] = tempy1/c1_index;

        mean[2][0] = tempx2/c2_index;
        mean[2][1] = tempy2/c2_index;

        mean[3][0] = tempx3/c3_index;
        mean[3][1] = tempy3/c3_index;

        mean[4][0] = tempx4/c4_index;
        mean[4][1] = tempy4/c4_index;


        // Convergance Step
        //to break the loop once the previous and current mean are equal
        if(prev_mean[0][0]==mean[0][0] && prev_mean[0][1]==mean[0][1] &&
           prev_mean[1][0]==mean[1][0] && prev_mean[1][1]==mean[1][1] &&
           prev_mean[2][0]==mean[2][0] && prev_mean[2][1]==mean[2][1] &&
           prev_mean[3][0]==mean[3][0] && prev_mean[3][1]==mean[3][1] &&
           prev_mean[4][0]==mean[4][0] && prev_mean[4][1]==mean[4][1]
           )
            flag=1;
        l ++;
    }
    printf("------------Cluster Euclidean distance---------\n");
    printf("%f %f, ---  %f %f  --- %f %f --- %f %f --- %f %f\n",mean[0][0], mean[0][1], mean[1][0], mean[1][1],
                                                                    mean[2][0], mean[2][1], mean[3][0], mean[3][1],
                                                                    mean[4][0], mean[4][1]);

    int clstr = 0;
    for(i=0; i<count; i++)
        {
          clstr = cluster[i];
          dist += sqrt((pow(mean[clstr][0]-datax[i],2))+(pow(mean[clstr][1]-datay[i],2)));

        }
        fprintf(fp, "error = %.3f \n", dist);
        for(i=0; i<count; i++)
        {
            fprintf(fp, "Point %d X Axis : %f\t Y Axis : %f\tCluster %d\n", i+1,datax_org[i], datay_org[i], cluster[i]);
            printf(" %f | %f = %d\n",datax_org[i], datay_org[i], cluster[i]);

        }
}


main(){

    FILE *fp = fopen("k_input.csv","r");

    int i=0;

    //to count the number of data points
    int count = 0;
    char buffer[1024];
    while (fgets(buffer,
                     1024, fp)) {
        count++;
    }

    rewind(fp);     //to bring the pointer at the beginning

    float sdx, sdy, meanx, meany, tempx=0, tempy=0;
    float datax[count], datay[count], datax_org[count], datay_org[count], sumx=0, sumy=0;

    //retrieving data from file


    int row = 0;
    int column = 0;

    while (fgets(buffer,
                     1024, fp)) {
         column = 0;
         row++;
         char* value = strtok(buffer, ", ");
         while (value) {
            if (column == 0) {
                 datax[i] = atof(value);
                 datax_org[i] = atof(value);
                 sumx += datax[i];
                }
            // Column 2
            if (column == 1) {
                datay[i] = atof(value);
                datay_org[i] = atof(value);
                sumy += datay[i];
                }

            value = strtok(NULL, ", ");
            column++;
            }
         i++;

         }
    rewind(fp);     //to bring the pointer at the beginning

    //mean of x and y feature
    meanx = sumx/count;
    meany = sumy/count;

    i=0;
    while(i<count)
    {
        tempx += pow(abs(datax[i] - meanx), 2);
        tempy += pow(abs(datay[i] - meany), 2);
        i++;
    }

    //standard deviation of x, y feature
    sdx = sqrt(tempx/(count-1));
    sdy = sqrt(tempy/(count-1));

    //preparing the standardized data
    i=0;
    while(i<count)
    {
        datax[i] = (datax[i]-meanx)/sdx;
        datay[i] = (datay[i]-meany)/sdy;
        i++;
    }
    //function call
    kmean(count, datax, datay, datax_org, datay_org);

}

