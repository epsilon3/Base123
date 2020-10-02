// Base123_Help.cpp : displays console-based system  help

////////////////////////////////////////////////////////////////////////////////
//
//  Base123 main application:
//
//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil)
//  Biological Informatics Group, RHDJ, 711HPW, United States Air Force Research Laboratory
//  05 October 2016
//  (All Rights Reserved)
//
////////////////////////////////////////////////////////////////////////////////

#include "Base123.h"
#include "Base123_Help.h"

////////////////////////////////////////////////////////////////////////////////
//
//  Writes Base123 help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportBase123Help()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123 Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil)\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  22 June 2016\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  General Usage is: Base123 <switch> <arg>/<opt>\n";
		cout << "//\n";
		cout << "//  Where <switch> is a Base123 command, <arg> is a required input, and <opt>\n";
		cout << "//       is optional input;\n";
		cout << "//\n";
		cout << "//  To get help on a specific Base123 component, use:\n";
		cout << "//\n";
		cout << "//       NCBI Management (All Things NCBI-related):\n";
		cout << "//            Base123 -help_ncbi_management [-hnm];\n";
		cout << "//\n";
		cout << "//       Base123 Catalog Managemenet:\n";
		cout << "//            Base123 -help_catalog_management [-hcm];\n";
		cout << "//\n";
		cout << "//       Genomic Sequence Shuffler Management:\n";
		cout << "//            Base123 -help_shuffler_management [-hsm;\n";
		cout << "//\n";
		cout << "//       Fofanov-Distance Analysis and Management:\n";
		cout << "//            Base123 -help_fdistance_management [-hfm];\n";
		cout << "//\n";
		cout << "//       Nucleotide Polymer Fold Management:\n";
		cout << "//            Base123 -help_nucleotide_fold_management [-hnfm];\n";
		cout << "//\n";
		cout << "//       Nucleotide Polymer Structure Analysis and Management:\n";
		cout << "//            Base123 -help_structure_ome_management [-hsom];\n";
		cout << "//\n";
		cout << "//       File and System Management:\n";
		cout << "//            Base123 -help_file_system_management [-hfsm];\n";
		cout << "//\n";
		cout << "//       NOTE:  Base123 supports file path naming via use of string-based\n";
		cout << "//            transforms (e.g., to use local file name only, leave the\n";
		cout << "//            transform string empty, to use full file path name, provide\n";
		cout << "//            the transform and include a combination of hard-coded elements\n";
		cout << "//            and run-time replacements [described within help for specific\n";
		cout << "//            algorithms]);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportBase123Help] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes NCBI management help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportNCBIManagementHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_NCBI_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil)\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  22 June 2016\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  General Usage is: Base123 <switch> <arg>/<opt>\n";
		cout << "//\n";
		cout << "//  Where <switch> is a Base123 command, <arg> is a required input, and <opt>\n";
		cout << "//       is optional input;\n";
		cout << "//\n";
		cout << "//  To get help on a specific NCBI management function, use:\n";
		cout << "//\n";
		cout << "//       Parse NCBI .fna/fa File List to BIG .fa File Format:\n";
		cout << "//            Base123 -help_parse_fna_to_fa [-hpftf];\n";
		cout << "//\n";
		cout << "//       Parse BIG Format .fa File List to BIG .pORF Format Files:\n";
		cout << "//            Base123 -help_parse_fa_to_porf [-hpftp];\n";
		cout << "//\n";
		cout << "//       Parse BIG Format .pORF File List to BIG .ORF Format Files:\n";
		cout << "//            Base123 -help_parse_porf_to_orf [-hppto];\n";
		cout << "//\n";
		cout << "//       NOTE:  Base123 supports file path naming via use of string-based\n";
		cout << "//            transforms (e.g., to use local file name only, leave the\n";
		cout << "//            transform string empty, to use full file path name, provide\n";
		cout << "//            the transform and include a combination of hard-coded elements\n";
		cout << "//            and run-time replacements [described within help for specific\n";
		cout << "//            algorithms]);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportNCBIManagementHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes Base123 catalog management help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportCatalogManagementHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_Catalog Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil)\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  22 June 2016\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  General Usage is: Base123 <switch> <arg>/<opt>\n";
		cout << "//\n";
		cout << "//  Where <switch> is a Base123 command, <arg> is a required input, and <opt>\n";
		cout << "//       is optional input;\n";
		cout << "//\n";
		cout << "//  To get help on a specific Base123 catalog management function, use:\n";
		cout << "//\n";
		cout << "//       Create a BIG Format Genome Catalog from NCBI .dat/_na.dat Files:\n";
		cout << "//            Base123 -help_create_dat_catalog [-hcdc];\n";
		cout << "//\n";
		cout << "//       Create a BIG Format Genome Catalog from NCBI .gbk Files:\n";
		cout << "//            Base123 -help_create_gbk_catalog [-hcgc];\n";
		cout << "//\n";
		cout << "//       NOTE:  Base123 supports file path naming via use of string-based\n";
		cout << "//            transforms (e.g., to use local file name only, leave the\n";
		cout << "//            transform string empty, to use full file path name, provide\n";
		cout << "//            the transform and include a combination of hard-coded elements\n";
		cout << "//            and run-time replacements [described within help for specific\n";
		cout << "//            algorithms]);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportCatalogManagementHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes Base123 Shuffler and FRESH help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportShufflerManagementHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_FRESH and Base123_Shuffler Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil)\n";
		cout << "//       and Brian Ervin\n";
		cout << "//       (Brian.Ervin.1.ctr@us.af.mil)\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  22 June 2016\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  General Usage is: Base123 <switch> <arg>/<opt>\n";
		cout << "//\n";
		cout << "//  Where <switch> is a Base123 command, <arg> is a required input, and <opt>\n";
		cout << "//       is optional input;\n";
		cout << "//\n";
		cout << "//  To get help on a specific Base123 Shuffler/FRESH function, use:\n";
		cout << "//\n";
		cout << "//       List shuffle (FRESH) BIG .fa Format File(s):\n";
		cout << "//            Base123 -help_list_shuffle_fa_files [-hlsff];\n";
		cout << "//\n";
		cout << "//       NOTE:  Base123 supports file path naming via use of string-based\n";
		cout << "//            transforms (e.g., to use local file name only, leave the\n";
		cout << "//            transform string empty, to use full file path name, provide\n";
		cout << "//            the transform and include a combination of hard-coded elements\n";
		cout << "//            and run-time replacements [described within help for specific\n";
		cout << "//            algorithms]);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportShufflerManagementHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes Base123 F-Distance analysis help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportFDistanceManagementHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_FDistance Developed by Yuriy Fofanov, PhD\n";
		cout << "//       (yfofanov@utmb.edu)\n";
		cout << "//       University of Texas Medical Branch;\n";
		cout << "//       and Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil)\n";
		cout << "//       and Jared Willard\n";
		cout << "//       (Jared.Willard.ctr@us.af.mil)\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  22 June 2016\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  General Usage is: Base123 <switch> <arg>/<opt>\n";
		cout << "//\n";
		cout << "//  Where <switch> is a Base123 command, <arg> is a required input, and <opt>\n";
		cout << "//       is optional input;\n";
		cout << "//\n";
		cout << "//  To get help on a specific Base123 F-Distance function, use:\n";
		cout << "//\n";
		cout << "//       Perform F-Distance Analysis:\n";
		cout << "//            Base123 -help_perform_fdistance_analysis [-hpfd];\n";
		cout << "//\n";
		cout << "//       Filter a BIG FA Format File List for F-Distance Analysis Suitability:\n";
		cout << "//            Base123 -help_list_filter_for_fdistance [-hlfff];\n";
		cout << "//\n";
		cout << "//       Contabulate a BIG F-Distance Output (Genomic and shuffles, Combined\n";
		cout << "//            with Foreground Catalog Metadata):\n";
		cout << "//            Base123 -help_list_contabulate_fdistance_output [-hlcfo];\n";
		cout << "//\n";
		cout << "//       Clear BIG F-Distance Output:\n";
		cout << "//            Base123 -help_list_clear_fdistance_output [-hlclfo];\n";
		cout << "//\n";
		cout << "//       NOTE:  Base123 supports file path naming via use of string-based\n";
		cout << "//            transforms (e.g., to use local file name only, leave the\n";
		cout << "//            transform string empty, to use full file path name, provide\n";
		cout << "//            the transform and include a combination of hard-coded elements\n";
		cout << "//            and run-time replacements [described within help for specific\n";
		cout << "//            algorithms]);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportFDistanceManagementHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes Base123 F-Distance analysis help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportNucleotideFoldManagementHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_Fold Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil)\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  22 June 2016\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  General Usage is: Base123 <switch> <arg>/<opt>\n";
		cout << "//\n";
		cout << "//  Where <switch> is a Base123 command, <arg> is a required input, and <opt>\n";
		cout << "//       is optional input;\n";
		cout << "//\n";
		cout << "//  To get help on a specific Base123 nucleotide polymer fold function, use:\n";
		cout << "//\n";
		cout << "//       List Fold BIG Format .pORF File(s):\n";
		cout << "//            Base123 -help_list_fold_files [-hlff];\n";
		cout << "//\n";
		cout << "//       List Confirm Fold Output File(s) (by Standard .ORF file name) via\n";
		cout << "//            Transform:\n";
		cout << "//            Base123 -help_list_confirm_fold_output_files [-hlcfof];\n";
		cout << "//\n";
		cout << "//       NOTE:  Base123 supports file path naming via use of string-based\n";
		cout << "//            transforms (e.g., to use local file name only, leave the\n";
		cout << "//            transform string empty, to use full file path name, provide\n";
		cout << "//            the transform and include a combination of hard-coded elements\n";
		cout << "//            and run-time replacements [described within help for specific\n";
		cout << "//            algorithms]);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportNucleotideFoldManagementHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes Base123 structureome analysis/management help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportStructureomeManagementHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_Structureome_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil)\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  22 May 2017\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  General Usage is: Base123 <switch> <arg>/<opt>\n";
		cout << "//\n";
		cout << "//  Where <switch> is a Base123 command, <arg> is a required input, and <opt>\n";
		cout << "//       is optional input;\n";
		cout << "//\n";
		cout << "//  To get help on a specific Base123 structurome analysis/management function,\n";
		cout << "//       use:\n";
		cout << "//\n";
		cout << "//       List Extract .PDB from Silent (*.out) Files:\n";
		cout << "//            Base123 -help_list_extract_pdb_from_silent_files [-hlepfsf];\n";
		cout << "//\n";
		cout << "//       List Convert .PDB to Dot-Bracket (*.fold) File Format:\n";
		cout << "//            Base123 -help_list_convert_pdb_to_db_files [-hlcptdf];\n";
		cout << "//\n";
		cout << "//       List Tabulate ViennaRNA Fold Output File(s):\n";
		cout << "//            Base123 -help_list_tabulate_vrna_output [-hltvo];\n";
		cout << "//\n";
		cout << "//       List Tabulate Rosetta Fold Output File(s):\n";
		cout << "//            Base123 -help_list_tabulate_rosa_output [-hltro];\n";
		cout << "//\n";
		cout << "//       NOTE:  Base123 supports file path naming via use of string-based\n";
		cout << "//            transforms (e.g., to use local file name only, leave the\n";
		cout << "//            transform string empty, to use full file path name, provide\n";
		cout << "//            the transform and include a combination of hard-coded elements\n";
		cout << "//            and run-time replacements [described within help for specific\n";
		cout << "//            algorithms]);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportStructureomeManagementHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes Base123 file system management help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportFileSystemManagementHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil)\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  22 June 2016\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  General Usage is: Base123 <switch> <arg>/<opt>\n";
		cout << "//\n";
		cout << "//  Where <switch> is a Base123 command, <arg> is a required input, and <opt>\n";
		cout << "//       is optional input;\n";
		cout << "//\n";
		cout << "//  To get help on a specific Base123 file manager function, use:\n";
		cout << "//\n";
		cout << "//       Create an HPC Distributed Batch Job From a File List:\n";
		cout << "//            Base123 -help_create_distributed_batch_job [-hcdbj];\n";
		cout << "//\n";
		cout << "//       Convert Full File Path Name List to File Name (Only) List:\n";
		cout << "//            Base123 -help_list_convert_path [-hlcp];\n";
		cout << "//\n";
		cout << "//       Find and Replace Text in File:\n";
		cout << "//            Base123 -help_file_find_replace [-hffr];\n";
		cout << "//\n";
		cout << "//       List Delete File(s) (Delete ALL Files in Input List):\n";
		cout << "//            Base123 -help_list_delete_files [-hldf];\n";
		cout << "//\n";
		cout << "//       List Delete File(s) in Directory (Delete ALL Files in Input List\n";
		cout << "//            Using Path Name Transform to Identify Directory):\n";
		cout << "//            Base123 -help_list_delete_files_in_directory [-hldfid];\n";
		cout << "//\n";
		cout << "//       List Transform Rename File(s) (Rename ALL Files in Input List):\n";
		cout << "//            Base123 -help_list_transform_rename_files [-hltrf];\n";
		cout << "//\n";
		cout << "//       List Match-Replace Rename File(s) (Rename ALL Files in Input List):\n";
		cout << "//            Base123 -help_list_match_replace_rename_files [-hlmrrf];\n";
		cout << "//\n";
		cout << "//       List Confirm Output Files (Confirms File Output via Transforms):\n";
		cout << "//            Base123 -help_list_confirm_output_files [-hlcof];\n";
		cout << "//\n";
		cout << "//       List Compare Differential File(s) (Compares From-List to To-List\n";
		cout << "//            and Reports Differences):\n";
		cout << "//            Base123 -help_list_compare_differential_files [-hlcdf];\n";
		cout << "//\n";
		cout << "//       NOTE:  Base123 supports file path naming via use of string-based\n";
		cout << "//            transforms (e.g., to use local file name only, leave the\n";
		cout << "//            transform string empty, to use full file path name, provide\n";
		cout << "//            the transform and include a combination of hard-coded elements\n";
		cout << "//            and run-time replacements [described within help for specific\n";
		cout << "//            algorithms]);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportFileSystemManagementHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes List Parse NCBI .fna/.fa File Format to BIG .fa File Format Help
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListParseFNAtoFAHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Parses a List of NCBI .fna/.fa Format Files into BIG .fa Format Files;\n";
		cout << "//       Files;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  6 July 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6> <arg7>;\n";
		cout << "//\n";
		cout << "//  -list_parse_fna_to_fa [-lpftf]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <output_file_path_name_transform>...\n";
		cout << "//       <sub_folder_list>...\n";
		cout << "//       <fna_output_list_file_path_name>...\n";
		cout << "//       <fa_output_list_file_path_name>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  output file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^DEFAULT_EXTENSION^ <default file extension>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <full file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "//  NOTE:  sub-folder list MUST be in nested order, delimited by '~';\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListParseFNAtoFAHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes List Parse BIG .fa File Format to BIG .pORF File Format Help
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListParseFAtoPORFHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Parses a List of BIG .fa Format Files into BIG .pORF Format Files;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  6 July 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6> <arg7>;\n";
		cout << "//\n";
		cout << "//  -list_parse_fa_to_porf [-lpftp]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       <min_orf_length>...\n";
		cout << "//       <max_orf_length>...\n";
		cout << "//       <output_list_file_path_name>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListParseFAtoPORFHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes List Parse BIG .pORF File Format to BIG .ORF File Format Help
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListParsePORFtoORFHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Parses List of BIG .pORF Format Files into BIG .ORF Format Files;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  6 July 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>...\n";
		cout << "//       <arg7> <arg8>;\n";
		cout << "//\n";
		cout << "//  -list_parse_porf_to_orf [-lppto]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       <orf_folder_name>...\n";
		cout << "//       <min_orf_length>...\n";
		cout << "//       <max_orf_length>...\n";
		cout << "//       <output_list_file_path_name>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListParsePORFtoORFHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes parse GBK container file help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListParseGBKContainerHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Parses a List of NCBI .gbk Format Container Files into Individual NCBI\n";
		cout << "//      .gbk Format Files;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  6 July 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5>;\n";
		cout << "//\n";
		cout << "//  -list_parse_gbk_container [-lpgc]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <output_file_path_name_transform>...\n";
		cout << "//       <output_list_file_path_name>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  output file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^DEFAULT_EXTENSION^ <default file extension>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListParseGBKContainerHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes .dat catalog help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportDatCatalogHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Creates a BIG format genome data catalog from NCBI .dat and _na.dat file\n";
		cout << "//       format;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  6 July 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>;\n";
		cout << "//\n";
		cout << "//  -create_dat_catalog [-cdc]...\n";
		cout << "//       <dat_input_file_path_name>...\n";
		cout << "//       <na_dat_input_file_path_name>...\n";
		cout << "//       <output_catalog_file_path_name>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>...\n";
		cout << "//       <max_catalog_size>;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportDatCatalogHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes GBK catalog help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportGBKCatalogHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Creates a BIG format genome data catalog from NCBI .gbk file format;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD;\n";
		cout << "//       (Stephen.Huff.3@us.af.mil);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  6 July 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>;\n";
		cout << "//\n";
		cout << "//  -create_gbk_catalog [-cgc]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       <output_catalog_file_path_name>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>...\n";
		cout << "//       <max_catalog_size>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportGBKCatalogHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  shuffles a .fa BIG file format into individual shuffle file(s)
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportFRESHHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  shuffles a .fa BIG file format into individual shuffle file(s);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_FRESH Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil) \n";
		cout << "//       and Brian Ervin (BErvin@gmail.com);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  23 July 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>...\n";
		cout << "//    <arg7> <arg8>;\n";
		cout << "//\n";
		cout << "//  -list_shuffle_fa_files [-lsff]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       <catalog_file_path_name>...\n";
		cout << "//       <max_catalog_size>...\n";
		cout << "//       <output_count>...\n";
		cout << "//       <output_list_file_path_name>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListParseGBKContainerHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes F-Distance filter help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportFilterFDistanceListHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Filters a BIG FA format file list for F-Distance analysis suitability;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil)\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  7 Aug 2016\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6> <arg7>;\n";
		cout << "//\n";
		cout << "//  -list_filter_for_fdistance [-lfff]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       -use_strict_filter [-usf]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -use_lax_filter [-ulf]...\n";
		cout << "//       <max_poly_unknowns>...\n";
		cout << "//       <accept_output_list_file_path_name>...\n";
		cout << "//       <reject_output_list_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "//  NOTE:  strict filter rejects any file with any unknown character\n";
		cout << "//       (any character except a, c, g, t/u), otherwise the filter rejects\n";
		cout << "//       only files containing poly-n and indeterminate gaps (-);\n";
		cout << "//\n";
		cout << "//  NOTE:  maximum poly unknown characters sets the maximum poly-limit\n";
		cout << "//       for all unknown characters except indeterminate gaps (-) (which\n";
		cout << "//       always reject) when strict filter is set; otherwise, it sets the;\n";
		cout << "//       the poly-n limit (should be at least one less than the intended\n";
		cout << "//       nMer size of the F-Distance analysis);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportBase123Help] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes F-Distance contabulation help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListContabulateFDistanceOutputHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Contabulates BIG F-Distance output from genomic and shuffled F-Distance\n";
		cout << "//       output files, combining them with the foreground genome's catalog;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil)\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  9 Sep 2016\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>...\n";
		cout << "//       <arg7> <arg8> <arg9>;\n";
		cout << "//\n";
		cout << "//  -list_contabulate_fdistance_output [-lcfo]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       <output_table_file_path_name>...\n";
		cout << "//       <catalog_file_path_name>...\n";
		cout << "//       <max_catalog_size>...\n";
		cout << "//       <output_count>...\n";
		cout << "//       <output_file_name_suffix>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  file path name list refers to the original BIG format FA file\n";
		cout << "//       list input into the original F-Distance run as the foreground\n";
		cout << "//       genome set;\n";
		cout << "//\n";
		cout << "//  NOTE:  input file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "//  NOTE:  catalog file path name is the foreground catalog of the original\n";
		cout << "//       F-Distance analysis;\n";
		cout << "//\n";
		cout << "//  NOTE:  output count must match the output count for original shuffles;\n";
		cout << "//\n";
		cout << "//  NOTE:  output file name suffix must match the output file name suffix\n";
		cout << "//       of the original F-Distance analysis;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportBase123Help] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes F-Distance output file(s) clearance help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListClearFDistanceOutputHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Clears BIG F-Distance output files;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil)\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  12 Sep 2016\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>;\n";
		cout << "//\n";
		cout << "//  -list_clear_fdistance_output [-lclfo]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       <output_count>...\n";
		cout << "//       <output_file_name_suffix>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  file path name list refers to the original BIG format FA file\n";
		cout << "//       list input into the original F-Distance run as the foreground\n";
		cout << "//       genome set;\n";
		cout << "//\n";
		cout << "//  NOTE:  input file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "//  NOTE:  output count must match the output count for original shuffles;\n";
		cout << "//\n";
		cout << "//  NOTE:  output file name suffix must match the output file name suffix\n";
		cout << "//       of the original F-Distance analysis;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportBase123Help] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes F-Distance help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportPerformFDistanceAnalysisHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  F-Distance Performs Fofanov Distance Genomic Analysis; compares a\n";
		cout << "//       foreground genome to a background genome to determine genomic distance\n";
		cout << "//       at the nucleotide polymer level using non-heuristic mutational\n";
		cout << "//       analysis;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  F-Distance Developed by Yuriy Fofanov, PhD (UTMB, yfofanov@utmb.edu),\n";
		cout << "//       Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil),\n";
		cout << "//       and Jared Willard (HIP Intern, Miami University);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  6 July 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>...\n";
		cout << "//       <arg7> <arg8> <arg9> <arg10> <arg11> <arg11> <arg11> <arg11>...\n";
		cout << "//       <arg11> <arg12> <arg13> <arg14>;\n";
		cout << "//\n";
		cout << "//  -perform_fdistance_analysis [-pfda]...\n";
		cout << "//       <output_table_file_path_name>...\n";
		cout << "//       <background_input_file_path_name_list>...\n";
		cout << "//       <background_input_file_path_name_transform>...\n";
		cout << "//       <background_catalog_file_path_name>...\n";
		cout << "//       <max_background_catalog_size>...\n";
		cout << "//       -background_unidirect [-bu]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -background_bidirect [-bb]...\n";
		cout << "//       -background_allow_unknowns [-bau]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -background_disallow_unknowns [-bdu]...\n";
		cout << "//       <background_error_file_path_name>...\n";
		cout << "//       <foreground_input_file_path_name_list>...\n";
		cout << "//       <foreground_input_file_path_name_transform>...\n";
		cout << "//       <foreground_catalog_file_path_name>...\n";
		cout << "//       <max_foreground_catalog_size>...\n";
		cout << "//       -foreground_unidirect [-fu]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -foreground_bidirect [-fb]...\n";
		cout << "//       -foreground_allow_unknowns [-fau]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -foreground_disallow_unknowns [-fdu]...\n";
		cout << "//       <foreground_error_file_path_name>...\n";
		cout << "//       <output_file_name_suffix>...\n";
		cout << "//       <nmer_length> (8, 16)...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input file path name transforms can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportPerformFDistanceAnalysisHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes list fold (Generic) .pORF or .ORF BIG format files help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListFoldFilesHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  List fold .pORF or .ORF BIG format files using generic application (e.g.,\n";
		cout << "//       ViennaRNA, Rosetta, etc...);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil),\n";
		cout << "//     Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  05 Oct 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>...\n";
		cout << "//       <arg7> <arg8> <arg9> <arg10> <arg11> <arg12> <arg13> <arg14>...\n";
		cout << "//        <arg15> <arg16> <arg17> <arg18> <arg19>;\n";
		cout << "//\n";
		cout << "//  -list_fold_files [-lff]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       -porf_file_list [-pfl]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -orf_file_list [-ofl]...\n";
		cout << "//       -no_overwrite_files [-nof]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -overwrite_files [-of]...\n";
		cout << "//       -thread_mode_process [-tmp]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -thread_mode_system [-tms]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -thread_mode_popen [-tmpn]...\n";
		cout << "//       <working_directory>...\n";
		cout << "//       <application_file_path_name>...\n";
		cout << "//       <application_parameters>...\n";
		cout << "//       <output_file_path_name_transform>...\n";
		cout << "//       <overwrite_file_path_name_transform>...\n";
		cout << "//       <after_file_path_name_transforms>...\n";
		cout << "//       <length_multiplier_factor>...\n";
		cout << "//       <orf_folder_name>...\n";
		cout << "//       <min_orf_length>...\n";
		cout << "//       <max_orf_length>...\n";
		cout << "//       <orf_output_list_file_name_suffix>...\n";
		cout << "//       <output_list_file_path_name>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input list files must be in BIG .pORF format;\n";
		cout << "//\n";
		cout << "//  NOTE:  input file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "//  NOTE:  -porf_file_list [-pfl] indicates input list contains .pORF file path\n";
		cout << "//       names; -orf_file_list [-ofl] indicates input list contains .ORF file\n";
		cout << "//       path names;\n";
		cout << "//\n";
		cout << "//  NOTE:  thread mode indicates the execution model at the .ORF list level;\n";
		cout << "//       the thread mode works in coordination with the working directory;\n";
		cout << "//       thread_mode_system and thread_mode_popen support an initial\n";
		cout << "//       change to a single working directory path (no transforms), while\n";
		cout << "//       thread_mode_process supports individual working directory changes\n";
		cout << "//       according to .ORF file path (allows transforms);\n";
		cout << "//\n";
		cout << "//  NOTE:  working directory can be a directory path or a transform that\n";
		cout << "//       can contain the following string replacement(s); use of\n";
		cout << "//       thread_mode_system or thread_mode_popen do NOT allow transforms,\n";
		cout << "//       while thread_mode_process supports the following transforms:\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "//  NOTE:  parameters can contain the following string replacements;\n";
		cout << "//       derived from .ORF file path name:\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension)...\n";
		cout << "//       ^INPUT_FILE_PATH_NAME^ <input file path name>...\n";
		cout << "//       ^OUTPUT_FILE_PATH_NAME^ <output file path name>...\n";
		cout << "//       ^OUTPUT_FILE_NAME^ <output file name> (no path)...\n";
		cout << "//       ^VRNA_FILE_NAME^ <ViennaRNA file name> (no path) see vendor site...\n";
		cout << "//       ^LENGTH_MULTIPLIER^ <multiply sequence length by this number>;\n";
		cout << "//\n";
		cout << "//  NOTE:  parameters ^OUTPUT_FILE_PATH_NAME^ replacement source is the\n";
		cout << "//       transform of the <output_file_path_name_transform> parameter\n";
		cout << "//       (see below);\n";
		cout << "//\n";
		cout << "//  NOTE:  output file transform SHOULD contain one or more of the\n";
		cout << "//       following string replacements; derived from .ORF file path name:\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^ORF_ORIENTATION^ <ORF orientation [f/r]>...\n";
		cout << "//       ^WORKING_DIRECTORY^ <working_directory>;\n";
		cout << "//\n";
		cout << "//  NOTE:  overwrite file transform can contain all the previous transforms;\n";
		cout << "//       if provided, it identifies the file overwrite target; if it is\n";
		cout << "//       blank, then the output file path transform is used to identify\n";
		cout << "//       the overwrite target; transforms derive from output file path name;\n";
		cout << "//\n";
		cout << "//  NOTE:  after file transforms contain the same file transform\n";
		cout << "//       replacement strings, and are used to rename output files after\n";
		cout << "//       fold operations; multiple transforms (per input file) delmited;\n";
		cout << "//       derived from output file path name:\n";
		cout << "//       <in~out&in~out&...>; PLUS:\n";
		cout << "//       ^FNELEAS^\n";
		cout << "//            <full file name except last extension and suffix> (no path,\n";
		cout << "//            minus last extension and fold output list suffix)...\n";
		cout << "//\n";
		cout << "//  NOTE:  length multiplier factor determines Monte Carlo cycles by length,\n";
		cout << "//       where cycles = length X length_multiplier_factor;\n";
		cout << "//\n";
		cout << "//  NOTE:  ORF folder name specifies a folder path relative to the input file\n";
		cout << "//       file path name used to temporarily store .ORF file output (these\n";
		cout << "//       file(s) are not retained after fold);\n";
		cout << "//\n";
		cout << "//  NOTE:  output list file name suffix is used to create the list of fold\n";
		cout << "//       file names created during the fold operation for each input .pORF\n";
		cout << "//       file (list contains file names relative to .pORF base path);\n";
		cout << "//       to avoid overwrite, this suffix should be fold-application-specific;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListFoldPORFFilesHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes list confirm fold file(s) help text to console
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListConfirmFoldOutputFilesHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Confirm fold file output file(s) (by standard .ORF file name) via\n";
		cout << "//       transforms; \n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil),\n";
		cout << "//     Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  13 Oct 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>...\n";
		cout << "//        <arg7> <arg8> <arg9> <arg10>;\n";
		cout << "//\n";
		cout << "//  -list_confirm_fold_output_files [-lcfof]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       <output_file_path_name_transform>...\n";
		cout << "//       <orf_folder_name>...\n";
		cout << "//       <min_orf_length>...\n";
		cout << "//       <max_orf_length>...\n";
		cout << "//       <missing_porf_list_file_path_name>...\n";
		cout << "//       <missing_orf_list_file_path_name>...\n";
		cout << "//       <analytical_output_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input file path name transform should describe original .pORF\n";
		cout << "//       file path names;\n";
		cout << "//\n";
		cout << "//  NOTE:  input/output file path name transform can contain the following\n";
		cout << "//       string replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//       ^VRNA_FILE_NAME^ <ViennaRNA file name> (no path) see vendor site...\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListConfirmFoldOutputFilesHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes list extract PDB from Rosetta silent (*.out) files help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListExtractPDBFromSilentFilesHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  List extract .PDB files from Rosetta silent (*.out) file format;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil),\n";
		cout << "//     Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  22 June 2017;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>;\n";
		cout << "//       <arg7> <arg8> <arg9> <arg10> <arg11> <arg12>;\n";
		cout << "//\n";
		cout << "//  -list_extract_pdb_from_silent_files [-lepfsf]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       -no_overwrite_files [-nof]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -overwrite_files [-of]...\n";
		cout << "//       -thread_mode_process [-tmp]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -thread_mode_system [-tms]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -thread_mode_popen [-tmpn]...\n";
		cout << "//       <working_directory>...\n";
		cout << "//       <application_file_path_name>...\n";
		cout << "//       <application_parameters>...\n";
		cout << "//       <overwrite_file_path_name_transform>...\n";
		cout << "//       <after_file_path_name_transforms>...\n";
		cout << "//       <output_list_file_path_name>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input list files must be in Rosetta silent (*.out) file format;\n";
		cout << "//\n";
		cout << "//  NOTE:  input file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "//  NOTE:  thread mode indicates the execution model at the .ORF list level;\n";
		cout << "//       the thread mode works in coordination with the working directory;\n";
		cout << "//       thread_mode_system and thread_mode_popen support an initial\n";
		cout << "//       change to a single working directory path (no transforms), while\n";
		cout << "//       thread_mode_process supports individual working directory changes\n";
		cout << "//       according to .ORF file path (allows transforms);\n";
		cout << "//\n";
		cout << "//  NOTE:  working directory can be a directory path or a transform that\n";
		cout << "//       can contain the following string replacement(s); use of\n";
		cout << "//       thread_mode_system or thread_mode_popen do NOT allow transforms,\n";
		cout << "//       while thread_mode_process supports the following transforms:\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "//  NOTE:  parameters can contain the following string replacements;\n";
		cout << "//       derived from .ORF file path name:\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension)...\n";
		cout << "//       ^INPUT_FILE_PATH_NAME^ <input file path name>...\n";
		cout << "//\n";
		cout << "//  NOTE:  overwrite file transform SHOULD contain one or more of the\n";
		cout << "//       following string replacements; derived from .ORF file path name:\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^ORF_ORIENTATION^ <ORF orientation [f/r]>...\n";
		cout << "//       ^WORKING_DIRECTORY^ <working_directory>;\n";
		cout << "//\n";
		cout << "//  NOTE:  overwrite file transform can contain all the previous transforms;\n";
		cout << "//       if provided, it identifies the file overwrite target; if it is\n";
		cout << "//       blank, then the output file path transform is used to identify\n";
		cout << "//       the overwrite target; transforms derive from output file path name;\n";
		cout << "//\n";
		cout << "//  NOTE:  after file transforms contain the same file transform\n";
		cout << "//       replacement strings, and are used to rename output files after\n";
		cout << "//       fold operations; multiple transforms (per input file) delmited;\n";
		cout << "//       derived from output file path name:\n";
		cout << "//       <in~out&in~out&...>; PLUS:\n";
		cout << "//       ^FNELEAS^\n";
		cout << "//            <full file name except last extension and suffix> (no path,\n";
		cout << "//            minus last extension and fold output list suffix)...\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListExtractPDBFromSilentFilesHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes list convert PDB to dot-bracket files help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListConvertPDBToB123FilesHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  List convert Rosetta PDB output file(s) (*.pdb) to Base123 (*.b123) file\n";
		cout << "//       format;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil),\n";
		cout << "//     Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  22 June 2017;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>;\n";
		cout << "//\n";
		cout << "//  -list_convert_db_to_base123_files [-lcdtbf]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       <output_file_path_name_transform>...\n";
		cout << "//       <output_list_file_path_name>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input list files must be in Rosetta PDB (*.pdb) format;\n";
		cout << "//\n";
		cout << "//  NOTE:  input file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "//  NOTE:  parameters can contain the following string replacements;\n";
		cout << "//       derived from .ORF file path name:\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension)...\n";
		cout << "//       ^INPUT_FILE_PATH_NAME^ <input file path name>...\n";
		cout << "//       ^OUTPUT_FILE_PATH_NAME^ <output file path name>...\n";
		cout << "//       ^OUTPUT_FILE_NAME^ <output file name> (no path)...\n";
		cout << "//       ^VRNA_FILE_NAME^ <ViennaRNA file name> (no path) see vendor site...\n";
		cout << "//       ^LENGTH_MULTIPLIER^ <multiply sequence length by this number>;\n";
		cout << "//\n";
		cout << "//  NOTE:  parameters ^OUTPUT_FILE_PATH_NAME^ replacement source is the\n";
		cout << "//       transform of the <output_file_path_name_transform> parameter\n";
		cout << "//       (see below);\n";
		cout << "//\n";
		cout << "//  NOTE:  output file transform SHOULD contain one or more of the\n";
		cout << "//       following string replacements; derived from .ORF file path name:\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^ORF_ORIENTATION^ <ORF orientation [f/r]>...\n";
		cout << "//       ^WORKING_DIRECTORY^ <working_directory>;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListConvertPDBToB123FilesHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes list convert DB to dot-bracket files help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListConvertDBtoB123FilesHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  List convert ViennaRNA dot-bracket output file(s) (*.fold) to Base123\n";
		cout << "//       (*.b123) file format;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil),\n";
		cout << "//     Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  22 June 2017;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>;\n";
		cout << "//\n";
		cout << "//  -list_convert_db_to_base123_files [-lcdtbf]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       <output_file_path_name_transform>...\n";
		cout << "//       <output_list_file_path_name>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input list files must be in ViennaRNA (*.out) format;\n";
		cout << "//\n";
		cout << "//  NOTE:  input file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "//  NOTE:  parameters can contain the following string replacements;\n";
		cout << "//       derived from .ORF file path name:\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension)...\n";
		cout << "//       ^INPUT_FILE_PATH_NAME^ <input file path name>...\n";
		cout << "//       ^OUTPUT_FILE_PATH_NAME^ <output file path name>...\n";
		cout << "//       ^OUTPUT_FILE_NAME^ <output file name> (no path)...\n";
		cout << "//       ^VRNA_FILE_NAME^ <ViennaRNA file name> (no path) see vendor site...\n";
		cout << "//       ^LENGTH_MULTIPLIER^ <multiply sequence length by this number>;\n";
		cout << "//\n";
		cout << "//  NOTE:  parameters ^OUTPUT_FILE_PATH_NAME^ replacement source is the\n";
		cout << "//       transform of the <output_file_path_name_transform> parameter\n";
		cout << "//       (see below);\n";
		cout << "//\n";
		cout << "//  NOTE:  output file transform SHOULD contain one or more of the\n";
		cout << "//       following string replacements; derived from .ORF file path name:\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^ORF_ORIENTATION^ <ORF orientation [f/r]>...\n";
		cout << "//       ^WORKING_DIRECTORY^ <working_directory>;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListConvertDBtoB123FilesHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes list tabulate Bse123 (*.b123) files help text to console;
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListTabulateB123FilesHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  List tabulate secondary structures from Base123 (*.b123) storage file(s);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil),\n";
		cout << "//     Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  22 May 2017;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5>;\n";
		cout << "//\n";
		cout << "//  -list_tabulate_base123_files [-ltbf]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       <output_table_file_path_name>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input list files must be in Base123 (*.b123) secondary structure\n";
		cout << "//       format; \n";
		cout << "//\n";
		cout << "//  NOTE:  input file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "//  NOTE:  parameters can contain the following string replacements;\n";
		cout << "//       derived from .ORF file path name:\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension)...\n";
		cout << "//       ^INPUT_FILE_PATH_NAME^ <input file path name>...\n";
		cout << "//       ^OUTPUT_FILE_PATH_NAME^ <output file path name>...\n";
		cout << "//       ^OUTPUT_FILE_NAME^ <output file name> (no path)...\n";
		cout << "//       ^VRNA_FILE_NAME^ <ViennaRNA file name> (no path) see vendor site...\n";
		cout << "//       ^LENGTH_MULTIPLIER^ <multiply sequence length by this number>;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListTabulateB123FilesHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes Create HPC Distributed Batch Job from File List Help
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportCreateDistributedBatchJobHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Create an HPC distributed batch job from a file list;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  20 October 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>...;\n";
		cout << "//       <arg7> <arg8> <arg9> <arg10> <arg11> <arg12> <arg13>;\n";
		cout << "//\n";
		cout << "//  -create_distributed_batch_job [-cdbj]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <output_list_file_path_name_transform>...\n";
		cout << "//       <queue_name>...\n";
		cout << "//       <wall_time>...\n";
		cout << "//       <job_name>...\n";
		cout << "//       <account_id>...\n";
		cout << "//       <application_name>...\n";
		cout << "//       <application_parameters>...\n";
		cout << "//       <project_path_name>...\n";
		cout << "//       <max_batches>...\n";
		cout << "//       -aprun_batch [-ab]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -qsub_batch [-qb]...\n";
		cout << "//       -make_list [-ml]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -skip_list [-sl]...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  <output_list_file_path_name_transform> can contain the following\n";
		cout << "//       string replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension)...\n";
		cout << "//       ^PROJECT_PATH_NAME^ <project path name>...\n";
		cout << "//       ^BATCH_NUMBER^ <batch number>...\n";
		cout << "//       ^PAD1_BATCH_NUMBER^ <1-digit padded batch number>...\n";
		cout << "//       ^PAD2_BATCH_NUMBER^ <2-digit padded batch number>...\n";
		cout << "//       ^PAD3_BATCH_NUMBER^ <3-digit padded batch number>...\n";
		cout << "//       ^PAD4_BATCH_NUMBER^ <4-digit padded batch number>;\n";
		cout << "//\n";
		cout << "//  NOTE:  <queue_name> must be [standard, debug, background];\n";
		cout << "//\n";
		cout << "//  NOTE:  <wall_time> format is [HH:MM:SS];\n";
		cout << "//\n";
		cout << "//  NOTE:  <job_name> length is 10 characters maximum; can contain\n";
		cout << "//       ^BATCH_NUMBER^ string replacement...\n";
		cout << "//       ^PAD1_BATCH_NUMBER^ <1-digit padded batch number>...\n";
		cout << "//       ^PAD2_BATCH_NUMBER^ <2-digit padded batch number>...\n";
		cout << "//       ^PAD3_BATCH_NUMBER^ <3-digit padded batch number>...\n";
		cout << "//       ^PAD4_BATCH_NUMBER^ <4-digit padded batch number>;\n";
		cout << "//\n";
		cout << "//  NOTE:  <account_id> must be valid HPC-specific account ID;\n";
		cout << "//\n";
		cout << "//  NOTE:  <application_name> length is 10 characters maximum;\n";
		cout << "//\n";
		cout << "//  NOTE:  <application_parameters> file path name(s) can contain the following\n";
		cout << "//       string replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension)...\n";
		cout << "//       ^PROJECT_PATH_NAME^ <project path name>...\n";
		cout << "//       ^BATCH_NUMBER^ <batch number>...\n";
		cout << "//       ^PAD1_BATCH_NUMBER^ <1-digit padded batch number>...\n";
		cout << "//       ^PAD2_BATCH_NUMBER^ <2-digit padded batch number>...\n";
		cout << "//       ^PAD3_BATCH_NUMBER^ <3-digit padded batch number>...\n";
		cout << "//       ^PAD4_BATCH_NUMBER^ <4-digit padded batch number>...\n";
		cout << "//       ^DQ^ <double quote>;\n";
		cout << "//\n";
		cout << "//  NOTE:  <project_path_name> will contain all project related files, if\n";
		cout << "//       <application_parameters> uses the ^PROJECT_PATH_NAME^ transform;\n";
		cout << "//\n";
		cout << "//  NOTE:  <max_batches> should indicate one batch per node;\n";
		cout << "//\n";
		cout << "//  NOTE:  -aprun_batch [-ab] causes the scripts to execute with aprun syntax (for\n";
		cout << "//              Cray systems); while -qsub_batch [-qb] causes the scripts to run on\n";
		cout << "//              the standard queue (other systems, e.g. SGI-Ice);\n";
		cout << "//\n";
		cout << "//  NOTE:  -make_list [-ml] splits the input list into batch lists; while\n";
		cout << "//              -skip_list [-sl] produces only the batch files;\n ";
		cout << "//\n";
		cout << "//  NOTE:  when using the -skip_list [-sl] option, <input_file_path_name_list>\n";
		cout << "//              is ignored and can be empty;\n ";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportCreateDistributedBatchJobHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes File List Conversion Help
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListConvertPathHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Converts a full file path name list to a file name (only) list;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  3 October 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4>;\n";
		cout << "//\n";
		cout << "//  -list_convert_path [-lcp]...\n";
		cout << "//       <input_file_path_name_list>...\n";
		cout << "//       <output_file_path_name_transform>...\n";
		cout << "//       <output_list_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  output file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListConvertPathHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes File Text Find/Replace Help
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportFileFindReplaceHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Finds and Replaces Text Within a File;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  4 October 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5>;\n";
		cout << "//\n";
		cout << "//  -file_find_replace [-ffr]...\n";
		cout << "//       <input_file_path_name>...\n";
		cout << "//       <output_file_path_name>...\n";
		cout << "//       <text_to_extract>...\n";
		cout << "//       <text_to_insert>...\n";
		cout << "//       -is_case_sensitive [-ics]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -not_case_sensitive [-ncs];\n";
		cout << "//\n";
		cout << "//  NOTE:  find/replace text can include the following control character\n";
		cout << "//       replacement(s):\n";
		cout << "//       \\r <carriage return character>...\n";
		cout << "//       \\n <new line character>...\n";
		cout << "//       \\t <tab character>;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportFileFindReplaceHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes List Delete Files Help
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListDeleteFilesHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Deletes ALL files in a list (NOTE:  delete is UNPROMPTED after execution);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  5 October 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4>;\n";
		cout << "//\n";
		cout << "//  -list_delete_files [-ldf]...\n";
		cout << "//       <input_file_path_name>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input file path name transform can contain the following string\n";
		cout << "//       replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListDeleteFilesHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes List Delete Files in Directory Help
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListDeleteFilesInDirectoryHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Deletes ALL files in a directory by file name list (NOTE:  delete is\n";
		cout << "//       UNPROMPTED after execution); \n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  11 October 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4>;\n";
		cout << "//\n";
		cout << "//  -list_delete_files_in_directory [-ldfid]...\n";
		cout << "//       <input_file_path_name>...\n";
		cout << "//       <delete_path_name_transform>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  delete path name indicates the directory from which all files should\n";
		cout << "//       be deleted (the directory, itself, is not deleted); delete path name\n";
		cout << "//       transform can contain wildcards and the following stringreplacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListDeleteFilesInDirectoryHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes list transform rename files help
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListTransformRenameFilesHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Renames all files in the list according to transforms; \n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  10 October 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5>;\n";
		cout << "//\n";
		cout << "//  -list_transform_rename_files [-ltrf]...\n";
		cout << "//       <input_file_path_name>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       <file_path_name_transforms>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input/output file path name transforms can contain the following\n";
		cout << "//       string replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "//  NOTE:  multiple transforms (per input file) delmited;\n";
		cout << "//       <in~out`in~out`...>; PLUS:\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListTransformRenameFilesHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes list match-and-replace rename files help
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListMatchReplaceRenameFilesHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Renames all files in the list according to transforms; \n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  10 October 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5>;\n";
		cout << "//\n";
		cout << "//  -list_match_replace_rename_files [-lmrrf]...\n";
		cout << "//       <input_file_path_name>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       <match_and_replace>...\n";
		cout << "//       <error_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input/output file path name transforms can contain the following\n";
		cout << "//       string replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "//  NOTE:  multiple transforms (per input file) delmited;\n";
		cout << "//       <in~out`in~out`...>; PLUS:\n";
		cout << "//\n";
		cout << "//  NOTE:  <match_and_replace> contains delimited match-and-replace string sets\n";
		cout << "//       in the following delimited format:\n";
		cout << "//       match_1~replace_1&match_2~replace_2&...;\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListMatchReplaceRenameFilesHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes list confirm output files help
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListConfirmOutputFilesHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Confirms listed files against output files via transforms and creates\n";
		cout << "//       missing files list; \n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  10 October 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5>;\n";
		cout << "//\n";
		cout << "//  -list_confirm_output_files [-lcof]...\n";
		cout << "//       <input_file_path_name>...\n";
		cout << "//       <input_file_path_name_transform>...\n";
		cout << "//       <output_file_path_name_transform>...\n";
		cout << "//       <missing_list_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  input/output file path name transforms can contain the following\n";
		cout << "//       string replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListConfirmOutputFilesHelp] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Writes list differential comparison help
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

void ReportListCompareDifferentialFilesHelp()
{
	try
	{
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Compares one file list to another and then lists differences (files\n";
		cout << "//       present in the from-list but not in the to-list); \n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Base123_File_Mgr Developed by Stephen Donald Huff, PhD\n";
		cout << "//       (Stephen.Huff.3@us.af.mil);\n";
		cout << "//       Biological Informatics Group, RHDJ, 711HPW, USAFRL;\n";
		cout << "//\n";
		cout << "//  10 October 2016;\n";
		cout << "//  (All Rights Reserved);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
		cout << "//\n";
		cout << "//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>;\n";
		cout << "//\n";
		cout << "//  -list_compare_differential_files [-lcdf]...\n";
		cout << "//       <input_file_path_name_from>...\n";
		cout << "//       <input_file_path_name_to>...\n";
		cout << "//       <file_path_name_transform>...\n";
		cout << "//       -multiset_diff [-msd]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -set_diff [-sd]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -vector_diff [-vd]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -list_diff [-ld]...\n";
		cout << "//            ...OR...\n";
		cout << "//                 -shell_diff [-shd]...\n";
		cout << "//       <output_list_file_path_name>...\n";
		cout << "//       <max_processors>;\n";
		cout << "//\n";
		cout << "//  NOTE:  from-list file should contain original files, while to-list should\n";
		cout << "//       contain comparison file(s) (e.g., files produced by some process, if\n";
		cout << "//       comparing process output to input);\n";
		cout << "//\n";
		cout << "//  NOTE:  output list file will contain file(s) without indicated output;\n";
		cout << "//\n";
		cout << "//  NOTE:  input/output file path name transforms can contain the following\n";
		cout << "//       string replacement(s):\n";
		cout << "//       ^BIG_ACCESSION^ <BIG format accession number>...\n";
		cout << "//       ^BASE_FILE_PATH_NAME^ <base file path name> (no extension)...\n";
		cout << "//       ^BASE_PATH^ <base path name> (no file name,  no extension)...\n";
		cout << "//       ^BASE_FILE_NAME^ <base file name> (no path, no extension)...\n";
		cout << "//       ^FNELE^\n";
		cout << "//            <full file name except last extension> (no path, minus last\n";
		cout << "//            extension only)...\n";
		cout << "//       ^FILE_NAME^ <file name> (no path, with full extension);\n";
		cout << "//\n";
		cout << "////////////////////////////////////////////////////////////////////////////////\n";
	}
	catch (exception ex)
	{
		cout << "ERROR [ReportListCompareDifferentialFilesHelp] Exception Code:  " << ex.what() << "\n";
	}
}
