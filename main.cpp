#include <cairo.h>
#include <gtk/gtk.h>
#include "UI_Handleing.h"
#include "File_interfacer.h"
#include "FileData.h"
#include "BasicId.h"

#include <iostream>

#include <Windows.h>
#include <string>


int main(int argc, char* argv[])
{
    BasicId test_id(L"11A111");
    if (test_id.valid()) {
        printf("True");
    }
    else {
        printf("False");
    }
    
    //UI_Handleing main_sim(argc, argv);
    return 0;
}
