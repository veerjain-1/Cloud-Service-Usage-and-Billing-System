#include "Cloud Service Usage and Billing System.h"
#include <stdio.h>
#include <string.h>

double calculate_bill(char *in_file, char *customer) {
    int days = 0, months = 0, years = 0;
    float servers = 0.0, hours = 0.0, network = 0.0, bytes = 0.0, blocks = 0.0;
    double total_bill = 0.0;
    char customer_type[50] = {};
    int data_found = 0;
    FILE *file = fopen(in_file, "r");
    if (file == NULL) {
        return FILE_READ_ERR;
    }
    while (1) {
        int index2 = fscanf(file, "%d/%d/%d|%[^|]|%f|%f|%f|%f/%f\n", &months, &days, &years, customer_type, &servers, &hours, &network, &bytes, &blocks);
        if (index2 == EOF) {
            break;
        } else if ((index2 != 9) || (servers < 0) || (hours < 0) || (network < 0) || (bytes < 0) || (blocks < 0)) {
            fclose(file);
            return BAD_RECORD;
        } else if ((months < 1) || (months > 12) || (days < 1) || (days > 30) || (years < 0)) {
            fclose(file);
            return BAD_DATE;
        } else if (strcmp(customer_type, customer) == 0) {
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

int generate_network_usage_report(char *in_file, char *customer, int year, char *out_file) {
    int days = 0, months = 0, years = 0;
    float servers = 0.0, hours = 0.0, bytes = 0.0, blocks = 0.0;
    int network = 0, data_found = 0;
    int monthly_totals[13] = {0};
    char customer_type[50] = {};

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
        int index = fscanf(input_file, "%d/%d/%d|%[^|]|%f|%f|%d|%f/%f\n", &months, &days, &years, customer_type, &servers, &hours, &network, &bytes, &blocks);
        if (index == EOF) {
            break;
        } else if ((index != 9) || (servers < 0) || (hours < 0) || (network < 0) || (bytes < 0) || (blocks < 0)) {
            fclose(input_file);
            fclose(output_file);
            return BAD_RECORD;
        } else if ((months < 1) || (months > 12) || (days < 1) || (days > 30) || (years < 0) || (year < 0)) {
            fclose(input_file);
            fclose(output_file);
            return BAD_DATE;
        } else if ((strcmp(customer_type, customer) == 0) && (year == years)) {
            monthly_totals[months] += network;
            data_found = 1;
        }
    }

    for (int i = 1; i <= 12; i++) {
        fprintf(output_file, "%02d:%d\n", i, monthly_totals[i]);
    }

    fprintf(output_file, "%04d\n", year);

    fclose(input_file);
    fclose(output_file);

    if (!data_found) {
        return NO_DATA_POINTS;
    }

    return SUCCESS;
}

int get_storage_usage(char *in_file, char *customer, int year) {
    int days = 0, months = 0, years = 0;
    float servers = 0.0, hours = 0.0, network = 0.0, bytes = 0.0, blocks = 0.0;
    int storage_usage = 0, data_found = 0;
    char customer_type[50] = {};
    FILE *file = fopen(in_file, "r");
    if (file == NULL) {
        return FILE_READ_ERR;
    }

    while (1) {
        int index2 = fscanf(file, "%d/%d/%d|%[^|]|%f|%f|%f|%f/%f\n", &months, &days, &years, customer_type, &servers, &hours, &network, &bytes, &blocks);
        if (index2 == EOF) {
            break;
        } else if ((index2 != 9) || (servers < 0) || (hours < 0) || (network < 0) || (bytes < 0) || (blocks < 0)) {
            fclose(file);
            return BAD_RECORD;
        } else if ((months < 1) || (months > 12) || (days < 1) || (days > 30) || (years < 0) || (year < 0)) {
            fclose(file);
            return BAD_DATE;
        } else if ((strcmp(customer_type, customer) == 0) && (year == years)) {
            storage_usage += bytes;
            data_found = 1;
        }
    }
    fclose(file);
    if (!data_found) {
        return NO_DATA_POINTS;
    }
    return storage_usage;
}

int get_network_usage(char *in_file, int month, int year) {
    FILE *inputfile = fopen(in_file, "r");
    if (inputfile == NULL) {
        return FILE_READ_ERR;
    }
    int days = 0, months = 0, years = 0;
    float servers = 0.0, hours = 0.0, network = 0.0, bytes = 0.0, blocks = 0.0;
    int network_usage = 0, data_found = 0;
    char customer_type[50] = {};

    while (1) {
        int index2 = fscanf(inputfile, "%d/%d/%d|%[^|]|%f|%f|%f|%f/%f\n", &months, &days, &years, customer_type, &servers, &hours, &network, &bytes, &blocks);
        if (index2 == EOF) {
            break;
        } else if ((index2 != 9) || (servers < 0) || (hours < 0) || (network < 0) || (bytes < 0) || (blocks < 0)) {
            fclose(inputfile);
            return BAD_RECORD;
        } else if ((months < 1) || (months > 12) || (days < 1) || (days > 30) || (years < 0) || (year < 0) || (month < 1) || (month > 12)) {
            fclose(inputfile);
            return BAD_DATE;
        } else if ((months == month) && (year == years)) {
            network_usage += network;
            data_found = 1;
        }
    }
    fclose(inputfile);
    if (!data_found) {
        return NO_DATA_POINTS;
    }
    return network_usage;
}
