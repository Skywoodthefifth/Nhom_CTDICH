#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int ERROR_STATE = 100;
typedef int state;            // kieu cac trang thai
typedef unsigned char *attri; // kieu cua thuoc tinh
typedef unsigned char *token; // kieu cua tu to
unsigned char *x;             // xau vao x ()
unsigned int i = 0;           // vi tri cua ky tu doc trong xau x

struct token_attri
{
    char tk[100];
    char a[100];

} tka[100];

int tka_len = 0;

unsigned char readchar(unsigned char *x, unsigned int i) // unsigned char : các số nguyên dương từ 0 đến 255
{
    // tra ve ky tu tiep theo, tương ứng với kí tự thứ i
    //    printf("i= %d , c= %c",i,*(x + i));
    if (i < strlen(x))
    {

        return (*(x + i));
    }
    else
    {
        return ('\0'); // \0 : null, được định nghĩa là 1 kí tự null- đó là 1 kí tự mà các bit đặt thành 0, sử dụng để chấm dứt chuỗi
    }
}

attri attribute(state s)
{
    // trả về thuộc tính tương ứng với trạng thái kết thúc
    // trả về thuộc tính của từ tố ( dựa vô ottomat) khi otomat rơi vào trạng thái kết thúc
    // char *ch = (char *)malloc(sizeof(char));

    char A[100];
    attri ch = A;

    switch (s)
    {
    case 2:
        strcpy(ch, "so sanh lon hon bang");
        break;
    case 3:
        strcpy(ch, "dich phai");
        break;
    case 4:
        strcpy(ch, "so sanh lon hon");
        break;
    case 6:
        strcpy(ch, "so sanh nho hon bang");
        break;
    case 7:
        strcpy(ch, "dich trai");
        break;
    case 8:
        strcpy(ch, "so sanh nho hon");
        break;
    case 10:
        strcpy(ch, "so sanh khong bang");
        break;
    case 11:
        strcpy(ch, "phu dinh");
        break;
    case 13:
        strcpy(ch, "so sanh bang");
        break;
    case 14:
        strcpy(ch, "gan");
        break;
    case 17:
        strcpy(ch, "cong bang");
        break;
    case 18:
        strcpy(ch, "tang 1");
        break;
    case 19:
        strcpy(ch, "cong");
        break;
    case 21:
        strcpy(ch, "tru bang");
        break;
    case 22:
        strcpy(ch, "giam 1");
        break;
    case 23:
        strcpy(ch, "tru");
        break;
    case 25:
        strcpy(ch, "nhan bang");
        break;
    case 26:
        strcpy(ch, "nhan");
        break;
    case 28:
        strcpy(ch, "chia bang");
        break;
    case 29:
        strcpy(ch, "chia");
        break;
    case 30:
        strcpy(ch, "chia lay du");
        break;

    case 48:
        strcpy(ch, "so nguyen he 8");
        break;
    case 51:
        strcpy(ch, "so nguyen he 16");
        break;
    case 52:
        strcpy(ch, "so 0");
        break;
    case 54:
        strcpy(ch, "so nguyen he 10");
        break;

    case 57:
        strcpy(ch, "so thuc");
        break;

    default:
        strcpy(ch, "token ko duoc doan nhan(tt ko dung \0");
    }

    return ch;
}

int nostar_end_state(state s)
{
    // kiểm tra s có phải là trạng thái kết thúc sao không - trả về 1 nếu không thuôc trạng thái sao
    switch (s)
    {
    case 2:
    case 3:
    case 6:
    case 7:
    case 10:
    case 13:
    case 17:
    case 18:
    case 21:
    case 22:
    case 25:
    case 28:
    case 30:
        //

        // case 48:
        // case 51:
        // case 52:
        // case 54:
        // case 57:
        return 1;
    default:
        return 0;
    }
} // sử dụng khi otomat chuyển trạng thái
// không gộp 2 thằng này được vì ngoài ra còn trường hợp 0 vs 15 là trạng thái băt đầu
int star_end_state(state s)
{
    // kiểm tra s có phải là trạng thái kết thúc sao không ( tức trạng thái kết thúc trả lui kí tự vừa đọc) - các trạng thái kết thúc có dấu sao
    switch (s)
    {
    case 4:
    case 8:
    case 11:
    case 14:
    case 19:
    case 23:
    case 26:
    case 29:
    //
    //
    case 48:
    case 51:
    case 52:
    case 54:
    case 57:

        return 1;
    default:
        return 0;
    }
}
state start_state_otherbrand(state s) // trả về trạng thái bắt đầu ( kiểm tra xem s là trạng thái bắt đầu nào và trả vể kiểu đó)
{                                     // trả về trạng thái bắt đầu hoặc trạng thái lỗi
    state start;
    // bởi vì ban đầu là star = 0 rồi nên giờ star = 15, nếu khác 15 sẽ lỗi
    switch (s)
    {
    case 0:
        start = 15; // 0 chuyển qua 15
        break;
    case 15:
        start = 45; // 15 ->45
        break;

    case 45:
        start = ERROR_STATE; // 45 ko có đường chuyển nên lỗi
        break;
    }
    return start;
}
int start_state(state s) // kiểm tra coi phải trạng thái bắt đầu không , tức TH 0 vs 15
{
    if ((s == 0) || (s == 15) || (s == 45))
        return 1;
    return 0;
}
void catchar_in_token(unsigned char c, token tk)
{
    // ghep them ky tu c vao cho tu to tk
    //    printf("lentk172=%d",strlen(tk));
    *(tk + strlen(tk) + 1) = '\0';
    *(tk + strlen(tk)) = c;

    // printf("tk = %s", tk);

    // printf("\n inchar = %c | ",*(tk+1));
    //  printf("\n inchar = %s | ",*tk);
}
token search_token(unsigned int *i, attri tt)
{
    // tra ve tri tu vung cua tu to bdau tu vi tri i, thuoc tinh tra ve cho tt
    // trả về vị trí từ vựng của từ tối ban đầu từ vị trí i, thuộc tính trả về cho tt
    // token tk = (unsigned char *)malloc(sizeof(unsigned char));

    char A[100] = "";
    token tk = A;

    //*(tk + 0) = ' ';

    state s = 0;
    int stop = 0;
    unsigned char c;
    do // đọc kí tự tương ứng với vị trí thứ i
    {
        c = readchar(x, *i); // trả về kí tự thứ i
        *i = *i + 1;

        if (c == '\n')
        {
            c = ' ';
        }

        // tăng con trỏ lên 1, để lần đọc tiếp theo sẽ đọc kí tự tiếp theo
    } while ((c == ' ') && (*i < strlen(x))); // nếu kí tự đọc được là kí tự rỗng và i chưa phải kí tự cuối thì đọc lại, tức bỏ qua kí tự trắng đó
                                              // khi đọc được c là kí tự khác kí tự trắng ( khi chưa đọc hết chuỗi)
                                              // chạy while để kiểm tra xem c là kí tự gì , rơi vào trường hợp nào
    //  printf("%c",c);
    *i = *i - 1;

    while (*i <= strlen(x) && (!stop))
    {
        // đầu tiên sẽ nhảy vào case 0, coi nó thuộc trường hợp 1 5 9 12 không, tức các trường hợp bên trái
        // nếu không thuộc thì nhảy qua case 15, tức bên phải, trạng thái bắt đầu là 15 ( thì sẽ chheck các TH 16 20 24 27 30)

        switch (s)
        {
        case 0:
            if (c == '>')
                s = 1;
            else if (c == '<')
                s = 5;
            else if (c == '!')
                s = 9;
            else if (c == '=')
                s = 12;
            else
                s = start_state_otherbrand(s); // kiểm tra coi s là trạng thái bắt đầu nào , 0 hay 15 ( vì rơi vào TH khác thì sẽ rơi vô Trạng thái bắt đầu)
            // cái ni chắc chắn trả về 15 để nhảy qua trạng thái bắt đầu khác
            // vì đã vô case 0 rồi thì nếu không rơi vào các TH trên thì chỉ có lỗi hoặc là trạng thái bắt đầu 15
            break;
        case 1:
            if (c == '=')
                s = 2;
            else if (c == '>')
                s = 3;
            else
                s = 4;
            break;
        case 5:
            if (c == '=')
                s = 6;
            else if (c == '<')
                s = 7;
            else
                s = 8;
            break;
        case 9:
            if (c == '=')
                s = 10;
            else
                s = 11;
            break;
        case 12:
            if (c == '=')
                s = 13;
            else
                s = 14;
            break;
        case 15:
            if (c == '+')
                s = 16;
            else if (c == '-')
                s = 20;
            else if (c == '*')
                s = 24;
            else if (c == '/')
                s = 27;
            else if (c == '%')
                s = 30;
            else
                s = start_state_otherbrand(s);
            // vì đây đã qua trạng thái bắt đầu 15 rồi nên nếu vô trương hợp khác thì chỉ có lỗi
            // còn như ở case 0 nếu vô TH khác thì có thể lỗi hoặc qua trạng thái bắt đầu 15
            break;
        case 16:
            if (c == '=')
                s = 17;
            else if (c == '+')
                s = 18;
            else
                s = 19;
            break;
        case 20:
            if (c == '=')
                s = 21;
            else if (c == '-')
                s = 22;
            else
                s = 23;
            break;
        case 24:
            if (c == '=')
                s = 25;
            else
                s = 26;
            break;
        case 27:
            if (c == '=')
                s = 28;
            else
                s = 29;
            break;

        case 45:
            if (c == '0')
            {
                s = 46;
            }
            else if (c >= '1' && c <= '9')
            {
                s = 53;
            }
            else if ('.')
            {
                s = 55;
            }
            else
                s = start_state_otherbrand(s);
            break;
        case 46: // 1
            if (c >= '0' && c <= '7')
            {
                s = 47; // so 2
            }
            else if (c == 'X' || c == 'x')
            {
                s = 49; // 4
            }
            else if (c == '.')
            {
                s = 55;
            }
            else
            {
                s = 52; // 7
            }
            break;
        case 47: // 2
            if (c >= '0' && c <= '7')
            {
                s = 47; // 2
            }
            // else if((c>='a'&&c<='z') || (c>='A'&&c<='Z')) {
            //     s = 55;//12
            // }
            else if (c == '.')
            {
                s = 55; // 10
            }
            else if (c >= '1' && c <= '9')
            { // kiem tra lai
                s = 53;
            }
            else
            {
                s = 48; // 3
            }
            break;
        case 49: // 4
            if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || (c >= '0' && c <= '9'))
            {
                s = 50; // 5
            }
            break;
        case 50: // 5
            if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || (c >= '0' && c <= '9'))
            {
                s = 50; // 5
            }
            else
            {
                s = 51; // 6
            }
            break;
        case 53:
            if (c >= '0' && c <= '9')
            {
                s = 53; // 10
            }
            else if (c == '.')
            {
                s = 55;
            }
            else
            {
                s = 54; // 11
            }
            break;
        case 55: // 12
            if (c >= '0' && c <= '9')
            {
                s = 56; // 12
            }
            break;
        case 56:
            if (c >= '0' && c <= '9')
            {
                s = 56; // 12
            }
            else
            {
                s = 57;
            }
            break;
        default:
            stop = 1;
        }

        // khi kiểm tra hắn rơi vào trường hợp nào rồi thì kiểm tra hắn coi thuộc trạng thái nào
        if (s == ERROR_STATE)
        {
            stop = 1;
            printf("loi tai ky tu thu %i", *i);
            *tk = '\0';
        }
        else if (start_state(s))
        {
            // nếu trang thái bắt đầu thì không làm gì cả, while sẽ chạy tiếp để đọc kí tự tiếp, ngược lại gặp các TH khác thì cho stop =1 để dừng vòng while
        }
        else if (nostar_end_state(s)) // nếu kí tự đọc mà khong phải trạng thái kết thúc sao thì ghép kí tự đó vào từ tố , vd : > thì gặp thêm dấu > thì ghép vô
        {                             // còn nếu > mà rơi vô TH * thì không ghép
                                      // vì TH * là phép so sánh nên kh ghép
            catchar_in_token(c, tk);  // ghép thêm kí tự c vào từ tố
            *i = *i + 1;              // Khi ghép vào từ tố rồi thì kí tự tiếp theo không cần đọc nữa, nên tăng con trỏ lên 1, để bỏ qua kí tự tiếp theo
            stop = 1;
            strcpy(tt, attribute(s));
            // printf("tt in search 1: %s\n", tt);
        }
        else if (star_end_state(s)) // nếu nó là trạng thái kết thúc sao thì không ghép nữa, ví dụ dấu > mà kí tự tiếp theo là 1 số thì không ghép
        {
            strcpy(tt, attribute(s));
            // printf("tt in search 2: %s\n", tt);
            stop = 1;
        }
        else // nếu mà gặp các kí tự không thuộc các phép thì cho vô TH ni, ví dụ gặp số hay chữ chi đó thì sẽ cho thành 1 từ tố
        {    // lúc này tăng con trỏ lên  1 để đọc kí tự tiếp theo luôn
            catchar_in_token(c, tk);

            *i = *i + 1;
            c = readchar(x, *i);
        }
    }

    return tk;
}
void save_token_and_attribute(token tk, attri a)
{
    // tka_len ++;
    // printf("tka_len in saves: %d\n", tka_len);
    strcpy(tka[tka_len].tk, tk);
    strcpy(tka[tka_len].a, a);
    tka_len++;
    // printf("tka in saves: %s\n", a);
}
void lexical_analysis()
{
    // token tk = (unsigned char *)malloc(sizeof(unsigned char));
    // attri a = (unsigned char *)malloc(sizeof(unsigned char));
    char A[100] = "";
    char B[100] = "";
    token tk = A;
    attri a = B;
    do
    {
        tk = search_token(&i, a); // đọc token từ đầu đến cuối, mỗi lần đọc trả về 1 kí tự cho đến khi đọc xong xâu thì thôi ( tức gặp kí tự /0 : kí tự kết thúc chuỗi hoặc i = strlen(x))
                                  // đọc từng token xong lưu nó vào danh sách
                                  // vì truyền vào địa chỉ của con trỏ i, nên mỗi lần đọc xong i tăng lên 1, lần đọc tiếp theo sẽ đọc từ vị trí i tiếp theo
        save_token_and_attribute(tk, a);
        // printf("tka in loop: %s\n", a);
    } while ((i < strlen(x)) || (*tk != '\0'));
    //
}
int main()
{
    // nhap xau vao x
    FILE *ptr;
    char ch;

    int n = 0;

    unsigned char temp[65536] = "";

    x = temp;

    // Opening file in reading mode
    ptr = fopen("text.txt", "r");

    if (NULL == ptr)
    {
        printf("file can't be opened \n");
    }

    // printf("content of this file are \n");

    // Printing what is written in file
    // character by character using loop.
    do
    {
        ch = fgetc(ptr);
        // printf("%c", ch);

        x[n++] = ch;

        // Checking if character is not EOF.
        // If it is EOF stop eading.
    } while (ch != EOF);

    // Closing the file
    fclose(ptr);

    printf("x = \n %s \n \n\n", x);

    // x = "< 0x7 16 15 += ++ /= 0 0.8  >> <";

    // Begin main algorithm
    i = 0;
    lexical_analysis();

    //
    //
    // Print result to file
    //

    FILE *fptr;
    fptr = fopen("result.txt", "w");

    if (fptr == NULL)
    {
        printf("file can't be opened \n");
    }

    for (int i = 0; i < tka_len - 2; i++)
    {
        fprintf(fptr, "token : %s , attribute : %s \n", tka[i].tk, tka[i].a);
    }

    fclose(fptr);
    // printf("tka_len: %d\n", tka_len);
    return 0;
}
