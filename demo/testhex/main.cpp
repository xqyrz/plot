#include <iostream>
#include <binfile.h>

int main()
{
    BinFile binFile("");
    binFile.load("F:/foc/V3.0/MOTOR/MDK-ARM/MOTOR/MOTOR.hex");
    return 0;
}