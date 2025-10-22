#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

int main(void)
{
    char in_path[260] = "Laba4.bin";   
    char out_path[260] = "Result.txt"; 
    int choice;
    FILE* fin = NULL, * fout = NULL, * flog = NULL; // файлові покажчики
    double x = 0.0, y = 0.0, z = 0.0;
    double result = 0.0, arctg = 0.0, exponent = 0.0;
    time_t t;
    char timebuf[64]; // буфер для форматування часу

    flog = fopen("program.log", "a");
    t = time(NULL); // отримання поточного системного часу
    strncpy(timebuf, ctime(&t), sizeof(timebuf)); 
    timebuf[strcspn(timebuf, "\n")] = 0;
    fprintf(flog, "[%s] Program started.\n", timebuf);

    printf("Enter X: "); scanf_s("%lf", &x);
    printf("Enter Y: "); scanf_s("%lf", &y);
    printf("Enter Z: "); scanf_s("%lf", &z);

    fin = fopen(in_path, "wb");
    fwrite(&x, sizeof(double), 1, fin);
    fwrite(&y, sizeof(double), 1, fin);
    fwrite(&z, sizeof(double), 1, fin);
    fclose(fin);

    fin = fopen(in_path, "rb");
    fread(&x, sizeof(double), 1, fin);
    fread(&y, sizeof(double), 1, fin);
    fread(&z, sizeof(double), 1, fin);
    fclose(fin);

    t = time(NULL);
    strncpy(timebuf, ctime(&t), sizeof(timebuf));
    timebuf[strcspn(timebuf, "\n")] = 0;
    fprintf(flog, "[%s] Parameters file \"%s\" opened. X=%.3f, Y=%.3f, Z=%.3f.\n", timebuf, in_path, x, y, z);

    arctg = atan(z);
    exponent = exp(-(x + 3));
    result = x * (arctg + exponent);

    t = time(NULL);
    strncpy(timebuf, ctime(&t), sizeof(timebuf));
    timebuf[strcspn(timebuf, "\n")] = 0;
    fprintf(flog, "[%s] Expression calculated. Result = %f\n", timebuf, result);

    printf("Select the output file format: 1 - text, 2 - binary : ");
    scanf_s("%d", &choice);

    if (choice == 2) {
        fout = fopen(out_path, "wb");
        fwrite(&result, sizeof(double), 1, fout);
    }
    else {
        fout = fopen(out_path, "w");
        fprintf(fout, "%f\n", result);
    }
    fclose(fout);

    t = time(NULL);
    strncpy(timebuf, ctime(&t), sizeof(timebuf));
    timebuf[strcspn(timebuf, "\n")] = 0;
    fprintf(flog, "[%s] Output file \"%s\" saved.\n", timebuf, out_path);
    fprintf(flog, "[%s] Program ended.\n\n", timebuf);
    fclose(flog);

    printf("Done. Result = %f\n", result);

    return 0;
}
