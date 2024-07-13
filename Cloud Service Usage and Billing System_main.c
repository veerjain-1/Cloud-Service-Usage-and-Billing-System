#include "hw2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * This function is used to run the functions implemented in hw2.c.
 * User input is used to determine which function to run what input
 * is passed to it. Upon completion, the function returns zero.
 */

int main() {
  int choice = 0;

  while (1) {
    printf(
      "Select a function to test:\n"
      "    1) calculate_bill()\n"
      "    2) generate_network_usage_report()\n"
      "    3) get_storage_usage()\n"
      "    4) get_network_usage()\n"
      "    5) Exit\n"
      "Enter your choice: "
    );

    scanf("%d", &choice);
    getchar();

    int month = 0;
    int year = 0;
    char customer[MAX_ID_LENGTH] = {0};
    char in_file[MAX_FILE_LENGTH] = {0};
    char out_file[MAX_FILE_LENGTH] = {0};

    switch (choice) {
      case 1:
        printf("Enter the input file name: ");
        scanf("%s", in_file);
        printf("Enter the customer: ");
        scanf("%s", customer);

        double bill = calculate_bill(in_file, customer);
        if (bill >= 0.0) {
          printf(
            "\ncalculate_bill(%s, %s) returned %f\n\n",
            in_file, customer, bill
          );
        }
        else {
          printf("\nError! (code %d)\n\n", (int) bill);
        }
        break;

      case 2:
        printf("Enter the input file name: ");
        scanf("%s", in_file);
        printf("Enter the customer: ");
        scanf("%s", customer);
        printf("Enter the year: ");
        scanf("%d", &year);
        printf("Enter the output file name: ");
        scanf("%s", out_file);

        int err_code = generate_network_usage_report(
          in_file, customer, year, out_file
        );
        if (err_code == SUCCESS) {
          printf(
            "\ngenerate_network_usage_report(%s, %s, %d, %s) "
            "returned SUCCESS\n", in_file, customer, year, out_file
          );
          printf(
            "Consider opening the output file to see its"
            "contents.\n\n"
          );
        }
        else {
          printf("Error! (code %d)\n", err_code);
        }
        break;

      case 3:
        printf("Enter the input file name: ");
        scanf("%s", in_file);
        printf("Enter the customer: ");
        scanf("%s", customer);
        printf("Enter the year: ");
        scanf("%d", &year);

        int storage = get_storage_usage(in_file, customer, year);
        if (storage >= 0) {
          printf(
            "\nget_storage_usage(%s, %s, %d) returned %d\n\n",
            in_file, customer, year, storage
          );
        }
        else {
          printf("\nError! (code %d)\n\n", storage);
        }
        break;

      case 4:
        printf("Enter the input file name: ");
        scanf("%s", in_file);
        printf("Enter the month: ");
        scanf("%d", &month);
        printf("Enter the year: ");
        scanf("%d", &year);

        int network = get_network_usage(in_file, month, year);
        if (network >= 0) {
          printf(
            "\nget_network_usage(%s, %d, %d) returned %d\n\n",
            in_file, month, year, network
          );
        }
        else {
          printf("\nError! (code %d)\n\n", network);
        }
        break;

      case 5:
        printf("\nGoodbye!\n\n");
        return 0;

      default:
        printf("\nSelect one of the given options...!\n\n");
        break;
    }
  }

  return 0;
} /* main() */
