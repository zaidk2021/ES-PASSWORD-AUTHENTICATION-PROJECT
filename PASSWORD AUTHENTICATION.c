#include <lpc17xx.h>
#define RS 27 // P0.27
#define EN 28 // P0.28
#define DT 23 // P0.23 to P0.26 data lines

unsigned long int temp1 = 0, temp2 = 0, i, j, x, count = 0, fail = 0, supcount = 0;
unsigned char flag1 = 0, flag2 = 0;
unsigned char ans;
unsigned char ams[10];
unsigned char op1, op2, oper, ans;
unsigned char msg[] = {"Enter the Password="};
unsigned char msg2[] = {"Checking the password "};
unsigned char msg3[] = {"succesfull authentication"};
unsigned char msg4[] = {"failed authentication retry "};
unsigned char msg5[] = {"all tries are over check again "};
unsigned char msg6[] = {"Enter the Password THAT SHOULD BE OF 4 CHARACTER"};
unsigned char msg7[] = {"IT SHOULD CONTAIN 2 NUMBER 2 ALPHABETS"};

unsigned long int s_pwd=0;
unsigned char msg8[] = {"STRONG PASSWORD"};
unsigned char msg9[] = {"AVERAGE PASSWORD"};
unsigned char msg10[] = {"WEAK PASSWORD"};


unsigned char message[4][4] = {{'1', '2', '3', '4'}, {'D', 'E', 'F', 'G'}, {'9', 'A', 'B', 'C'}, {'5', '6', '7', '8'}};

unsigned char entered_pwd[4];
unsigned char correct_pwd[4];

int help = 0;
unsigned char col, row, flag, key;
unsigned long var;
unsigned int r;
void scan();

void lcd_write(void);
void port_write(void);
void delay_lcd(unsigned int);
unsigned long int init_command[] = {0x30, 0x30, 0x30, 0x20, 0x28, 0x0c, 0x06, 0x01, 0x80};

void TIM1delay()
{
    LPC_TIM0->TCR = 0X02;
    LPC_TIM0->MCR = 0X02;
    LPC_TIM0->CTCR = 0X0;
    LPC_TIM0->EMR = 0X20;

    LPC_TIM0->PR = 2;
    LPC_TIM0->MR0 = 1999996;
    LPC_TIM0->TCR = 0X01;
    while (LPC_TIM0->EMR && 0X01 == 0)
        ;
}

void port_write1()
{
    // LPC_GPIO0->FIOPIN = flag1 << 27;
    LPC_GPIO0->FIOPIN = temp2 << 23;
    if (flag1 == 0)
        LPC_GPIO0->FIOCLR = 1 << 27; // RS command
    else
        LPC_GPIO0->FIOSET = 1 << 27; // RS data
    // sending command/data

    LPC_GPIO0->FIOSET = 1 << 28;
    for (i = 0; i < 50; i++)
        ;
    LPC_GPIO0->FIOCLR = 1 << 28;
    for (i = 0; i < 50000; i++)
        ;
}
void delay_lcd(unsigned int r1)
{

    for (r = 0; r < r1; r++)
        ;

    return;
}
void lcd_write1()
{
    temp2 = temp1 & 0xF0;
    temp2 = temp2 >> 4;
    port_write1();

    temp2 = (temp1 & 0x0F);
    port_write1();
}

int main(void)
{
    SystemInit();
    SystemCoreClockUpdate();
    LPC_GPIO0->FIODIR = 1 << RS | 1 << EN | 0XF << DT;
    LPC_PINCON->PINSEL3 &= 0xFFC03FFF; // P1.23 to P1.26 MADE
                                       // GPIO
    LPC_PINCON->PINSEL4 &= 0xF00FFFFF; // P2.10 t P2.13 made
                                       // GPIO
    LPC_GPIO2->FIODIR |= 0x00003C00;   // made output P2.10 to
                                       // P2.13 (rows)
    LPC_GPIO1->FIODIR &= 0xF87FFFFF;   // made input P1.23 to
                                       // P1.26 (cols)
    flag1 = 0;


// Write the commands in command register


    for (i = 0; i < 9; i++)
    {
        temp1 = init_command[i];
        lcd_write();
    }
    //_________________________________________________________________________________________________________________________________________

    flag1 = 1; // Write the data in data register
    i = 0;

    while (msg6[i] != '\0')
    {
        temp1 = msg6[i];
        lcd_write();
        i += 1;
        if (i == 16)
        {
            temp1 = 0xc0; // Enable  the second line and to write commands in command register
            flag1 = 0;
            lcd_write();
            flag1 = 1;
        }
    }
    delay_lcd(1500000);
    flag1 = 0;
    temp1 = 0x01;
    lcd_write();

    flag1 = 1; // Write the data in data register
    i = 0;

    //_____________________________________________________________________________________________________________________________________________________________
    j = 0;
    flag1 = 1;

    while (1)
    {

        for (row = 0; row < 4; row++)
        {
            LPC_GPIO2->FIOPIN = 1 << (10 + row);
            x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
            for (i = 0; i < 500; i++)
                ;
            if (x)
            {
                if (x == 1)
                    col = 0;
                else if (x == 2)
                    col = 1;
                else if (x == 4)
                    col = 2;
                else if (x == 8)
                    col = 3;
                temp1 = message[row][col];
                lcd_write1();
                for (i = 0; i < 1500000; i++)
                    ;
                help = 1;
                correct_pwd[0] = message[row][col];
            }
        }
        if (help == 1)
        {
            break;
        }
    }

    delay_lcd(1500000);
   flag1 = 0;
   temp1 = 0x01;
    lcd_write();

    //__________________________________________________________________________________________________________________________________
    j = 0;
    flag1 = 1;

    help = 0;

    while (1)
    {

        for (row = 0; row < 4; row++)
        {
            LPC_GPIO2->FIOPIN = 1 << (10 + row);
            x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
            for (i = 0; i < 500; i++)
                ;
            if (x)
            {
                if (x == 1)
                    col = 0;
                else if (x == 2)
                    col = 1;
                else if (x == 4)
                    col = 2;
                else if (x == 8)
                    col = 3;
                temp1 = message[row][col];
                lcd_write1();
                for (i = 0; i < 1500000; i++)
                    ;
                help = 1;
                correct_pwd[1] = message[row][col];
            }
        }
        if (help == 1)
        {
            break;
        }
    }

    delay_lcd(1500000);
    flag1 = 0;
    temp1 = 0x01;
    lcd_write();
    j = 0;
    flag1 = 1;

    //__________________________________________________________________________________________________________________________________

    help = 0;
    while (1)
    {

        for (row = 0; row < 4; row++)
        {
            LPC_GPIO2->FIOPIN = 1 << (10 + row);
            x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
            for (i = 0; i < 500; i++)
                ;
            if (x)
            {
                if (x == 1)
                    col = 0;
                else if (x == 2)
                    col = 1;
                else if (x == 4)
                    col = 2;
                else if (x == 8)
                    col = 3;
                temp1 = message[row][col];
                lcd_write1();
                for (i = 0; i < 1500000; i++)
                    ;
                help = 1;
                correct_pwd[2] = message[row][col];
            }
        }
        if (help == 1)
        {
            break;
        }
    }

    delay_lcd(1500000);
    flag1 = 0;
    temp1 = 0x01;
    lcd_write();
    j = 0;
    flag1 = 1;

    //__________________________________________________________________________________________________________________________________
    help = 0;
    while (1)
    {

        for (row = 0; row < 4; row++)
        {
            LPC_GPIO2->FIOPIN = 1 << (10 + row);
            x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
            for (i = 0; i < 500; i++)
                ;
            if (x)
            {
                if (x == 1)
                    col = 0;
                else if (x == 2)
                    col = 1;
                else if (x == 4)
                    col = 2;
                else if (x == 8)
                    col = 3;
                temp1 = message[row][col];
                lcd_write1();
                for (i = 0; i < 1500000; i++)
                    ;
                help = 1;
                correct_pwd[3] = message[row][col];
            }
        }
        if (help == 1)
        {
            break;
        }
    }

    delay_lcd(1500000);
    flag1 = 0;
    temp1 = 0x01;
    lcd_write();
    delay_lcd(1500000);


s_pwd=0;

for(i=0;i<4;i++)
{
if(correct_pwd[i]>='A' && correct_pwd[i]<='G')
{
s_pwd++;
}
}

delay_lcd(1500000);
    flag1 = 1;
    temp1 = s_pwd+0x30;
    lcd_write();
    delay_lcd(1500000);


if(s_pwd==4 || s_pwd== 3)
{

flag1 = 1; // Write the data in data register
i = 0;

while (msg8[i] != '\0')
{
temp1 = msg8[i];
lcd_write();
i += 1;
if (i == 16)
{
temp1 = 0xc0; // Enable  the second line and to write commands in command register
flag1 = 0;
lcd_write();
flag1 = 1;
}
}
delay_lcd(1500000);
flag1 = 0;
temp1 = 0x01;
lcd_write();

}
else if (s_pwd==2)
{

flag1 = 1; // Write the data in data register
i = 0;

while (msg9[i] != '\0')
{
temp1 = msg9[i];
lcd_write();
i += 1;
if (i == 16)
{
temp1 = 0xc0; // Enable  the second line and to write commands in command register
flag1 = 0;
lcd_write();
flag1 = 1;
}
}
delay_lcd(1500000);
flag1 = 0;
temp1 = 0x01;
lcd_write();


}
else
{

flag1 = 1; // Write the data in data register
i = 0;

while (msg10[i] != '\0')
{
temp1 = msg10[i];
lcd_write();
i += 1;
if (i == 16)
{
temp1 = 0xc0; // Enable  the second line and to write commands in command register
flag1 = 0;
lcd_write();
flag1 = 1;
}
}
delay_lcd(1500000);
flag1 = 0;
temp1 = 0x01;
lcd_write();


}


for(i=0;i<4;i++)
{
correct_pwd[i]= (correct_pwd[i]+'a');
}




    //_________________________________________________________________________________________________________________________________________
    //______________________________________________________
    //_____________________________________________________
    //____________________________________________________
    //___________________________________________________

    flag1 = 1; // Write the data in data register
    i = 0;
    //_________________________________________________________________________________________________________________________________________

    while (msg[i] != '\0')
    {
        temp1 = msg[i];
        lcd_write();
        i += 1;
        if (i == 16)
        {
            temp1 = 0xc0; // Enable  the second line and to write commands in command register
            flag1 = 0;
            lcd_write();
            flag1 = 1;
        }
    }
    delay_lcd(1500000);
    flag1 = 0;
    temp1 = 0x01;
    lcd_write();

    flag1 = 1;
   
help=0;

    j = 0;
    flag1 = 1;

    while (1)
    {

        for (row = 0; row < 4; row++)
        {
            LPC_GPIO2->FIOPIN = 1 << (10 + row);
            x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
            for (i = 0; i < 500; i++)
                ;
            if (x)
            {
                if (x == 1)
                    col = 0;
                else if (x == 2)
                    col = 1;
                else if (x == 4)
                    col = 2;
                else if (x == 8)
                    col = 3;
                temp1 = message[row][col];
                lcd_write1();
                for (i = 0; i < 1500000; i++)
                    ;
                help = 1;
                entered_pwd[0] = message[row][col];
            }
        }
        if (help == 1)
        {
            break;
        }
    }

    delay_lcd(1500000);
    flag1 = 0;
    temp1 = 0x01;
    lcd_write();

    //__________________________________________________________________________________________________________________________________
    j = 0;
    flag1 = 1;

    help = 0;

    while (1)
    {

        for (row = 0; row < 4; row++)
        {
            LPC_GPIO2->FIOPIN = 1 << (10 + row);
            x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
            for (i = 0; i < 500; i++)
                ;
            if (x)
            {
                if (x == 1)
                    col = 0;
                else if (x == 2)
                    col = 1;
                else if (x == 4)
                    col = 2;
                else if (x == 8)
                    col = 3;
                temp1 = message[row][col];
                lcd_write1();
                for (i = 0; i < 1500000; i++)
                    ;
                help = 1;
                entered_pwd[1] = message[row][col];
            }
        }
        if (help == 1)
        {
            break;
        }
    }

    delay_lcd(1500000);
    flag1 = 0;
    temp1 = 0x01;
    lcd_write();
    j = 0;
    flag1 = 1;

    //__________________________________________________________________________________________________________________________________

    help = 0;
    while (1)
    {

        for (row = 0; row < 4; row++)
        {
            LPC_GPIO2->FIOPIN = 1 << (10 + row);
            x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
            for (i = 0; i < 500; i++)
                ;
            if (x)
            {
                if (x == 1)
                    col = 0;
                else if (x == 2)
                    col = 1;
                else if (x == 4)
                    col = 2;
                else if (x == 8)
                    col = 3;
                temp1 = message[row][col];
                lcd_write1();
                for (i = 0; i < 1500000; i++)
                    ;
                help = 1;
                entered_pwd[2] = message[row][col];
            }
        }
        if (help == 1)
        {
            break;
        }
    }

    delay_lcd(1500000);
    flag1 = 0;
    temp1 = 0x01;
    lcd_write();
    j = 0;
    flag1 = 1;

    //__________________________________________________________________________________________________________________________________
    help = 0;
    while (1)
    {

        for (row = 0; row < 4; row++)
        {
            LPC_GPIO2->FIOPIN = 1 << (10 + row);
            x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
            for (i = 0; i < 500; i++)
                ;
            if (x)
            {
                if (x == 1)
                    col = 0;
                else if (x == 2)
                    col = 1;
                else if (x == 4)
                    col = 2;
                else if (x == 8)
                    col = 3;
                temp1 = message[row][col];
                lcd_write1();
                for (i = 0; i < 1500000; i++)
                    ;
                help = 1;
                entered_pwd[3] = message[row][col];
            }
        }
        if (help == 1)
        {
            break;
        }
    }

    delay_lcd(1500000);
    flag1 = 0;
    temp1 = 0x01;
    lcd_write();




    //_________________________________________________________________________________________________________________________________________
    help = 0;

    flag1 = 1; // Write the data in data register
    i = 0;

    while (msg2[i] != '\0')
    {
        temp1 = msg2[i];
        lcd_write();
        i += 1;
        if (i == 16)
        {
            temp1 = 0xc0; // Enable  the second line and to write commands in command register
            flag1 = 0;
            lcd_write();
            flag1 = 1;
        }
    }
    delay_lcd(1500000);
    flag1 = 0;
    temp1 = 0x01;
    lcd_write();

    //_________________________________________________________________________________________________________________________________________

    // checking the password

    for (i = 0; i < 4; i++)
    {
        if (entered_pwd[i] != correct_pwd[i]-'a')
        {
            fail = 1;
            break;
        }
    }

    if (fail == 0)
    {
        flag1 = 1; // Write the data in data register
        i = 0;
        while (msg3[i] != '\0')
        {
            temp1 = msg3[i];
            lcd_write();
            i += 1;
            if (i == 16)
            {
                temp1 = 0xc0; // Enable  the second line and to write commands in command register
                flag1 = 0;
                lcd_write();
                flag1 = 1;
            }
        }
        delay_lcd(1500000);
        flag1 = 0;
        temp1 = 0x01;
        lcd_write();
        supcount = 3;


    }
    else
    {
        flag1 = 1; // Write the data in data register
        i = 0;

        while (msg4[i] != '\0')
        {
            temp1 = msg4[i];
            lcd_write();
            i += 1;
            if (i == 16)
            {
                temp1 = 0xc0; // Enable  the second line and to write commands in command register
                flag1 = 0;
                lcd_write();
                flag1 = 1;
            }
        }
        delay_lcd(1500000);
        delay_lcd(1500000);
        flag1 = 0;
        temp1 = 0x01;
        lcd_write();

        flag1 = 1;
        i = 0;
        while (msg[i] != '\0')
        {
            temp1 = msg[i];
            lcd_write();
            i += 1;
            if (i == 16)
            {
                temp1 = 0xc0; // Enable  the second line and to write commands in command register
                flag1 = 0;
                lcd_write();
                flag1 = 1;
            }
        }
        delay_lcd(1500000);
        flag1 = 0;
        temp1 = 0x01;
        lcd_write();

        j = 0;
        flag1 = 1;

        while (1)
        {

            for (row = 0; row < 4; row++)
            {
                LPC_GPIO2->FIOPIN = 1 << (10 + row);
                x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
                for (i = 0; i < 500; i++)
                    ;
                if (x)
                {
                    if (x == 1)
                        col = 0;
                    else if (x == 2)
                        col = 1;
                    else if (x == 4)
                        col = 2;
                    else if (x == 8)
                        col = 3;
                    temp1 = message[row][col];
                    lcd_write1();
                    for (i = 0; i < 1500000; i++)
                        ;
                    help = 1;
                    entered_pwd[0] = message[row][col];
                }
            }
            if (help == 1)
            {
                break;
            }
        }

        delay_lcd(1500000);
        flag1 = 0;
        temp1 = 0x01;
        lcd_write();

        //__________________________________________________________________________________________________________________________________
        j = 0;
        flag1 = 1;

        help = 0;

        while (1)
        {

            for (row = 0; row < 4; row++)
            {
                LPC_GPIO2->FIOPIN = 1 << (10 + row);
                x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
                for (i = 0; i < 500; i++)
                    ;
                if (x)
                {
                    if (x == 1)
                        col = 0;
                    else if (x == 2)
                        col = 1;
                    else if (x == 4)
                        col = 2;
                    else if (x == 8)
                        col = 3;
                    temp1 = message[row][col];
                    lcd_write1();
                    for (i = 0; i < 1500000; i++)
                        ;
                    help = 1;
                    entered_pwd[1] = message[row][col];
                }
            }
            if (help == 1)
            {
                break;
            }
        }

        delay_lcd(1500000);
        flag1 = 0;
        temp1 = 0x01;
        lcd_write();
        j = 0;
        flag1 = 1;

        //__________________________________________________________________________________________________________________________________

        help = 0;
        while (1)
        {

            for (row = 0; row < 4; row++)
            {
                LPC_GPIO2->FIOPIN = 1 << (10 + row);
                x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
                for (i = 0; i < 500; i++)
                    ;
                if (x)
                {
                    if (x == 1)
                        col = 0;
                    else if (x == 2)
                        col = 1;
                    else if (x == 4)
                        col = 2;
                    else if (x == 8)
                        col = 3;
                    temp1 = message[row][col];
                    lcd_write1();
                    for (i = 0; i < 1500000; i++)
                        ;
                    help = 1;
                    entered_pwd[2] = message[row][col];
                }
            }
            if (help == 1)
            {
                break;
            }
        }

        delay_lcd(1500000);
        flag1 = 0;
        temp1 = 0x01;
        lcd_write();
        j = 0;
        flag1 = 1;

        //__________________________________________________________________________________________________________________________________
        help = 0;
        while (1)
        {

            for (row = 0; row < 4; row++)
            {
                LPC_GPIO2->FIOPIN = 1 << (10 + row);
                x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
                for (i = 0; i < 500; i++)
                    ;
                if (x)
                {
                    if (x == 1)
                        col = 0;
                    else if (x == 2)
                        col = 1;
                    else if (x == 4)
                        col = 2;
                    else if (x == 8)
                        col = 3;
                    temp1 = message[row][col];
                    lcd_write1();
                    for (i = 0; i < 1500000; i++)
                        ;
                    help = 1;
                    entered_pwd[3] = message[row][col];
                }
            }
            if (help == 1)
            {
                break;
            }
        }

        delay_lcd(1500000);
        flag1 = 0;
        temp1 = 0x01;
        lcd_write();

        //_________________________________________________________________________________________________________________________________________
        help = 0;

        flag1 = 1; // Write the data in data register
        i = 0;

        while (msg2[i] != '\0')
        {
            temp1 = msg2[i];
            lcd_write();
            i += 1;
            if (i == 16)
            {
                temp1 = 0xc0; // Enable  the second line and to write commands in command register
                flag1 = 0;
                lcd_write();
                flag1 = 1;
            }
        }
        delay_lcd(1500000);
        flag1 = 0;
        temp1 = 0x01;
        lcd_write();
        fail = 0;
        for (i = 0; i < 4; i++)
        {
            if (entered_pwd[i] != correct_pwd[i]-'a')
            {
                fail = 1;
                break;
            }
        }

        if (fail == 0)
        {
            flag1 = 1; // Write the data in data register
            i = 0;
            while (msg3[i] != '\0')
            {
                temp1 = msg3[i];
                lcd_write();
                i += 1;
                if (i == 16)
                {
                    temp1 = 0xc0; // Enable  the second line and to write commands in command register
                    flag1 = 0;
                    lcd_write();
                    flag1 = 1;
                }
            }
            delay_lcd(1500000);
            flag1 = 0;
            temp1 = 0x01;
            lcd_write();
            supcount = 3;
        }
        else
        {
            flag1 = 1; // Write the data in data register
            i = 0;

            while (msg4[i] != '\0')
            {
                temp1 = msg4[i];
                lcd_write();
                i += 1;
                if (i == 16)
                {
                    temp1 = 0xc0; // Enable  the second line and to write commands in command register
                    flag1 = 0;
                    lcd_write();
                    flag1 = 1;
                }
            }
            delay_lcd(1500000);
            delay_lcd(1500000);
            flag1 = 0;
            temp1 = 0x01;
            lcd_write();

            flag1 = 1;
            i = 0;
            while (msg[i] != '\0')
            {
                temp1 = msg[i];
                lcd_write();
                i += 1;
                if (i == 16)
                {
                    temp1 = 0xc0; // Enable  the second line and to write commands in command register
                    flag1 = 0;
                    lcd_write();
                    flag1 = 1;
                }
            }
            delay_lcd(1500000);
            flag1 = 0;
            temp1 = 0x01;
            lcd_write();

            j = 0;
            flag1 = 1;

            while (1)
            {

                for (row = 0; row < 4; row++)
                {
                    LPC_GPIO2->FIOPIN = 1 << (10 + row);
                    x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
                    for (i = 0; i < 500; i++)
                        ;
                    if (x)
                    {
                        if (x == 1)
                            col = 0;
                        else if (x == 2)
                            col = 1;
                        else if (x == 4)
                            col = 2;
                        else if (x == 8)
                            col = 3;
                        temp1 = message[row][col];
                        lcd_write1();
                        for (i = 0; i < 1500000; i++)
                            ;
                        help = 1;
                        entered_pwd[0] = message[row][col];
                    }
                }
                if (help == 1)
                {
                    break;
                }
            }

            delay_lcd(1500000);
            flag1 = 0;
            temp1 = 0x01;
            lcd_write();

            //__________________________________________________________________________________________________________________________________
            j = 0;
            flag1 = 1;

            help = 0;

            while (1)
            {

                for (row = 0; row < 4; row++)
                {
                    LPC_GPIO2->FIOPIN = 1 << (10 + row);
                    x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
                    for (i = 0; i < 500; i++)
                        ;
                    if (x)
                    {
                        if (x == 1)
                            col = 0;
                        else if (x == 2)
                            col = 1;
                        else if (x == 4)
                            col = 2;
                        else if (x == 8)
                            col = 3;
                        temp1 = message[row][col];
                        lcd_write1();
                        for (i = 0; i < 1500000; i++)
                            ;
                        help = 1;
                        entered_pwd[1] = message[row][col];
                    }
                }
                if (help == 1)
                {
                    break;
                }
            }

            delay_lcd(1500000);
            flag1 = 0;
            temp1 = 0x01;
            lcd_write();
            j = 0;
            flag1 = 1;

            //__________________________________________________________________________________________________________________________________

            help = 0;
            while (1)
            {

                for (row = 0; row < 4; row++)
                {
                    LPC_GPIO2->FIOPIN = 1 << (10 + row);
                    x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
                    for (i = 0; i < 500; i++)
                        ;
                    if (x)
                    {
                        if (x == 1)
                            col = 0;
                        else if (x == 2)
                            col = 1;
                        else if (x == 4)
                            col = 2;
                        else if (x == 8)
                            col = 3;
                        temp1 = message[row][col];
                        lcd_write1();
                        for (i = 0; i < 1500000; i++)
                            ;
                        help = 1;
                        entered_pwd[2] = message[row][col];
                    }
                }
                if (help == 1)
                {
                    break;
                }
            }

            delay_lcd(1500000);
            flag1 = 0;
            temp1 = 0x01;
            lcd_write();
            j = 0;
            flag1 = 1;

            //__________________________________________________________________________________________________________________________________
            help = 0;
            while (1)
            {

                for (row = 0; row < 4; row++)
                {
                    LPC_GPIO2->FIOPIN = 1 << (10 + row);
                    x = (LPC_GPIO1->FIOPIN >> 23) & 0xF;
                    for (i = 0; i < 500; i++)
                        ;
                    if (x)
                    {
                        if (x == 1)
                            col = 0;
                        else if (x == 2)
                            col = 1;
                        else if (x == 4)
                            col = 2;
                        else if (x == 8)
                            col = 3;
                        temp1 = message[row][col];
                        lcd_write1();
                        for (i = 0; i < 1500000; i++)
                            ;
                        help = 1;
                        entered_pwd[3] = message[row][col];
                    }
                }
                if (help == 1)
                {
                    break;
                }
            }

            delay_lcd(1500000);
            flag1 = 0;
            temp1 = 0x01;
            lcd_write();

            //_________________________________________________________________________________________________________________________________________
            help = 0;

            flag1 = 1; // Write the data in data register
            i = 0;

            while (msg2[i] != '\0')
            {
                temp1 = msg2[i];
                lcd_write();
                i += 1;
                if (i == 16)
                {
                    temp1 = 0xc0; // Enable  the second line and to write commands in command register
                    flag1 = 0;
                    lcd_write();
                    flag1 = 1;
                }
            }
            delay_lcd(1500000);
            flag1 = 0;
            temp1 = 0x01;
            lcd_write();
            fail = 0;
            for (i = 0; i < 4; i++)
            {
                if (entered_pwd[i] != correct_pwd[i]-'a')
                {
                    fail = 1;
                    break;
                }
            }

            if (fail == 0)
            {
                flag1 = 1; // Write the data in data register
                i = 0;
                while (msg3[i] != '\0')
                {
                    temp1 = msg3[i];
                    lcd_write();
                    i += 1;
                    if (i == 16)
                    {
                        temp1 = 0xc0; // Enable  the second line and to write commands in command register
                        flag1 = 0;
                        lcd_write();
                        flag1 = 1;
                    }
                }
                delay_lcd(1500000);
                flag1 = 0;
                temp1 = 0x01;
                lcd_write();
                supcount = 3;
            }
            else
            {
                flag1 = 1; // Write the data in data register
                i = 0;
                while (msg5[i] != '\0')
                {
                    temp1 = msg5[i];
                    lcd_write();
                    i += 1;
                    if (i == 16)
                    {
                        temp1 = 0xc0; // Enable  the second line and to write commands in command register
                        flag1 = 0;
                        lcd_write();
                        flag1 = 1;
                    }
                }
                delay_lcd(1500000);
                flag1 = 0;
                temp1 = 0x01;
                lcd_write();
                supcount = 3;
            }
        }
    }
}

void lcd_write(void)
{
    flag2 = (flag1 == 1) ? 0 : ((temp1 == 0x30) || (temp1 == 0x20)) ? 1
                                                                    : 0;
    temp2 = temp1 & 0xf0; // move data (26-8+1) times : 26 - HN place, 4 - Bits
    temp2 = temp2 >> 4;
    temp2 = temp2 << DT; // data lines from 23 to 26
    port_write();
    if (!flag2)
    {
        temp2 = temp1 & 0x0f; // 26-4+1
        temp2 = temp2 << DT;
        port_write();
    }
}

void port_write(void)
{
    LPC_GPIO0->FIOPIN = 0;
    LPC_GPIO0->FIOPIN = temp2;
    if (flag1 == 0)
        LPC_GPIO0->FIOCLR = 1 << RS;
    else
        LPC_GPIO0->FIOSET = 1 << RS;

    LPC_GPIO0->FIOSET = 1 << EN;
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = 1 << EN;
    delay_lcd(30000);
}
