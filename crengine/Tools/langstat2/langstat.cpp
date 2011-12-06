// langstat.cpp : Defines the entry point for the console application.
//

#include <stdlib.h>
#include <crengine.h>

#define DEST_FILE "cp_stats.cpp"

void MakeStatsForFile( const char * fname, const char * cp_name, const char * lang_name, int index, FILE * f, lString8 & list );

void MakeStats(FILE * src)
{
   lString8 list( 
      "typedef struct {\n"
      "    const short * ch_stat;\n"
      "    const dbl_char_stat_t * dbl_ch_stat;\n"
      "    char * cp_name;\n"
      "    char * lang_name;\n"
      "} cp_stat_t;\n"
      "\n\ncp_stat_t cp_stat_table[] = {\n"
      );
   FILE * f = fopen(DEST_FILE, "wt");
   if (!f)
      return;
   fprintf(f, 
	  "// LANGUAGE CODEPAGE AUTODETECTION STATISTICS FILE\n"
	  "// generated by CoolReader3 (c)Vadim Lopatin, 2005-2008\n\n"
      "#include \"../include/cp_stats.h\"\n\n"
      "#define NULL 0\n\n" );
      //"typedef struct {\n"
      //"   unsigned char ch1;\n"
      //"   unsigned char ch2;\n"
      //"   short    count;\n"
      //"} dbl_char_stat_t;\n\n#define NULL 0\n\n" );

#define MAX_LINE_LEN 1000
   char line[MAX_LINE_LEN+1];
   char filename[MAX_LINE_LEN+1];
   char encname[MAX_LINE_LEN+1];
   char langname[MAX_LINE_LEN+1];
   int id;
   while (fgets(line, MAX_LINE_LEN, src)) {
       line[MAX_LINE_LEN] = 0;
       if (sscanf(line, "%s %s %s %d\n", filename, encname, langname, &id) == 4) {
           printf("file: %s  cp:%s lang:%s id:%d\n", filename, encname, langname, id);
           MakeStatsForFile(filename, encname, langname, id, f, list);
       } else {
           fprintf(stderr, "skipping invalid source line: %s\n", line);
       }
   }
   fprintf( f, "%s{NULL, NULL, NULL, NULL}\n};\n\n", list.c_str() );
   fclose(f);
}


int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("usage: langstat <srclistfile>\n");
        printf("srclistfile format: lines like\n\n");
        printf("lang-samplefile1.txt encodingname langname sampleid\n");
        printf("rus1-cp1251.txt cp1251 ru 1\n");
        printf("rus2-cp1251.txt cp1251 ru 2\n\n");
        return -1;
    }
    FILE * src = fopen(argv[1], "rt");
    if (!src) {
        printf("File %s is not found\n", argv[1]);
        return -2;
    }
    MakeStats(src);
    fclose(src);
    return 0;
}