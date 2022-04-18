// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t BYTE;
typedef int16_t SAMPLE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
        // read first 44 bytes (HEADER_SIZE) of FILE *input:
        BYTE header_bytes[HEADER_SIZE]; // buffer of size HEADER_SIZE
        fread(header_bytes, sizeof(BYTE), HEADER_SIZE, input);

        // write into FILE *output the copied first 44 bytes (HEADER_SIZE) of FILE *input:
        fwrite(header_bytes, sizeof(BYTE), HEADER_SIZE, output);

    // TODO: Read samples from input file and write updated data to output file

        // get the size of the input file
            fseek(input, 0, SEEK_END); // move pointer to the end of 'input' (file)
            long long int  input_size_without_header = ftell(input) - 44;
            printf("size of input file without the header: %lld \n", input_size_without_header);
            long long int  input_size_without_header_for_sample = input_size_without_header / 2;


        // read samples in 'input' (file) [aka after the first 44 bytes]
        SAMPLE sample_bytes[input_size_without_header_for_sample]; // buffer of size input_size_without_header_for_sample
        fseek(input, 44, SEEK_SET);; // move pointer in 'input' (file) from the end of the file to the address right after the header
        long int starting_sample = ftell(input);
        printf("pointer at starting sample is: %ld\n", starting_sample);
        fread(sample_bytes, sizeof(SAMPLE), input_size_without_header_for_sample, input); //read into the samples' buffer every sample till the end of the file


        // printf("%ld \n", sizeof(sample_bytes)); // checking that size of buffer works?

        fseek(output, 0, HEADER_SIZE); // move pointer in 'output' (file) to the address right after the header
        SAMPLE revolumed_copy_of_sample_bytes[input_size_without_header_for_sample];
        for(int i = 0; i < input_size_without_header_for_sample; i++)
        {
            revolumed_copy_of_sample_bytes[i] = sample_bytes[i] * factor;
        }

        fwrite(revolumed_copy_of_sample_bytes, sizeof(SAMPLE), input_size_without_header_for_sample, output); // write into 'output' (file) samples from the buffer 'revolumed_copy_of_sample_bytes'


    // Close files
    fclose(input);
    fclose(output);
}
