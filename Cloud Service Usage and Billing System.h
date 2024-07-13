#ifndef Cloud Service Usage and Billing System
#define Cloud Service Usage and Billing System

#define FILE_READ_ERR -1
#define FILE_WRITE_ERR -2
#define BAD_RECORD -3
#define BAD_DATE -4
#define NO_DATA_POINTS -5
#define SUCCESS 0

double calculate_bill(char *in_file, char *customer);
int generate_network_usage_report(char *in_file, char *customer, int year, char *out_file);
int get_storage_usage(char *in_file, char *customer, int year);
int get_network_usage(char *in_file, int month, int year);

#endif
