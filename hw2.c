/* Veer Jain, hw2.c, CS 240, Spring 2024
 * Last updated Jan 24, 2023
 */

/* Add any includes here */
#include "hw2.h"
#include <stdio.h>
#include <string.h>

/* Define calculate_bill here */


double calculate_bill(char *in_file, char *customer) {
    int days, months, years;
    float servers, hours, network, bytes, blocks;
    double total_bill = 0.0;
    char customer_type[50];
    int data_found = 0;
    FILE *file = fopen(in_file, "r");
    if (file == NULL) {
        return FILE_READ_ERR;
    }
    while (1) {
        int index2 = fscanf(file, "%d/%d/%d|%[^|]|%f|%f|%f|%f/%f\n", &months, &days, &years, customer_type, &servers, &hours, &network, &bytes, &blocks);
        if(index2 == EOF){
            break;
        }
        else if(index2!=9 || servers<0 || hours<0 || network<0 || bytes < 0 || blocks<0){
            fclose(file);
            return BAD_RECORD;
        }
        else if (months<1 || months>12 || days<1 || days>31 || years<0){
            fclose(file);
            return BAD_DATE;
        }
        else if (strcmp(customer_type, customer) == 0) {
            double bill = (0.01 * network) + (0.02 * blocks) + (0.06 * servers * hours);
            total_bill += bill;
            data_found = 1;
        }
    }

    fclose(file);

    if (!data_found) {
        return NO_DATA_POINTS;
    }
    return total_bill;
}


/* Define generate_network_usage_report here */
int generate_network_usage_report(char *in_file, char *customer, int year, char *out_file) {
    int days, months, years;
    float servers, hours, network, bytes, blocks;
    char customer_type[50];
    int data_found = 0;
    FILE *input_file = fopen(in_file, "r");
    if (input_file == NULL) {
        return FILE_READ_ERR;
    }
    FILE *output_file = fopen(out_file, "w");
    if (output_file == NULL) {
        fclose(input_file);
        return FILE_WRITE_ERR;
    }

    fprintf(output_file, "%s\n", customer);
    while (1) {
        int index = fscanf(input_file, "%d/%d/%d|%49[^|]|%f|%f|%f|%f|%f\n", &months, &days, &years, customer_type, &servers, &hours, &network, &bytes, &blocks);
        if (index == EOF) {
            break;
        }
        else if (index != 9 || servers < 0 || hours < 0 || network < 0 || bytes < 0 || blocks < 0) {
            fclose(input_file);
            fclose(output_file);
            return BAD_RECORD;
        }
        else if (months < 1 || months > 12 || days < 1 || days > 31 || years < 0) {
            fclose(input_file);
            fclose(output_file);
            return BAD_DATE;
        }
        else if (strcmp(customer_type, customer) == 0 && year == years) {
            fprintf(output_file, "%d/%d/%d: %f\n", months, days, years, network);
            data_found = 1;
        }
    }

    fclose(input_file);
    fclose(output_file);

    if (!data_found) {
        return NO_DATA_POINTS;
    }

    return SUCCESS;
}
/* Define get_storage_usage here */
int get_storage_usage(char *in_file, char *customer, int year) {
    FILE *inputfile = fopen(in_file, "r");
    if (inputfile == NULL) {
        return FILE_READ_ERR;
    }

    int days, months, years, storageUsage = 0, data_found = 0;
    float servers, hours, network, bytes, blocks;
    char customer_type[50];

    int result;
    while ((result = fscanf(inputfile, "%d/%d/%d|%49[^|]|%f|%f|%f|%f|%f", &months, &days, &years, customer_type, &servers, &hours, &network, &bytes, &blocks)) != EOF) {
        if (result != 9) {
            fclose(inputfile);
            return BAD_RECORD;
        }
        if (strcmp(customer_type, customer) == 0 && year == years) {
            storageUsage += bytes;
            data_found = 1;
        }
    }

    fclose(inputfile);

    if (!data_found) {
        return NO_DATA_POINTS;
    }

    return storageUsage;
}


/* Define get_network_usage here */
int get_network_usage(char *in_file, int month, int year) {
    FILE *inputfile = fopen(in_file, "r");
    if (inputfile == NULL) {
        return FILE_READ_ERR;
    }

    int days, months, years, networkUsage = 0, data_found = 0;
    float servers, hours, network, bytes, blocks;
    char customer_type[50];

    while (fscanf(inputfile, "%d/%d/%d|%49[^|]|%f|%f|%f|%f|%f\n", &months, &days, &years, customer_type, &servers, &hours, &network, &bytes, &blocks) != EOF) {
        if (month == months && year == years) {
            networkUsage += network;
            data_found = 1;
        }
    }

    fclose(inputfile);

    if (!data_found) {
        return NO_DATA_POINTS;
    }

    return networkUsage;
}
