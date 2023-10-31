#ifndef HW2_H
#define HW2_H

/* Constant Definitions */
#define MAX_ID_LENGTH (50)
#define MAX_FILE_LENGTH (50)

/* Error Codes */
#define SUCCESS (0)
#define FILE_READ_ERR (-1)
#define FILE_WRITE_ERR (-2)
#define BAD_RECORD (-3)
#define NO_DATA_POINTS (-4)
#define BAD_DATE (-5)

/* You are not allowed to use access() */
#define access(x, y) (printf("\n\n\n\n\nDo not use access().\n"), abort(), 1)

/* Function Prototypes */
double calculate_bill(char *, char *);
int generate_network_usage_report(char *, char *, int, char *);
int get_storage_usage(char *, char *, int);
int get_network_usage(char *, int, int);

#endif // HW2_H