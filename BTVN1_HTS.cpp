#include <stdio.h>


///////////////PHAN CODE CAU 2///////////////
// Ham chuyen doi nhi phan sang thap phan
int binaryToDecimal(int n) {
    int decimal = 0, base = 1, remainder;
    while (n > 0) {
        remainder = n % 10;
        decimal = decimal + remainder * base;
        base = base * 2;
        n = n / 10;
    }
    return decimal;
}

// Ham chuyen doi thap phan sang nhi phan
int decimalToBinary(int n) {
    int binary = 0, base = 1, remainder;
    while (n > 0) {
        remainder = n % 2;
        binary = binary + remainder * base;
        base = base * 10;
        n = n / 2;
    }
    return binary;
}

// Cau 2: Phep cong/tru so nhi phan
void cau2() {
    int bin1_a = 100111, bin2_a = 110011; // Cau 2 a
    int bin1_b = 100111, bin2_b = 11010;  // Cau 2 b
    printf("\nCau 2:\n");

    // a) Phep cong
    int dec1_a = binaryToDecimal(bin1_a);
    int dec2_a = binaryToDecimal(bin2_a);
    int sum_a = dec1_a + dec2_a;
    printf("Phep cong a:\n");
    printf("Nhi phan: %d + %d = %d\n", bin1_a, bin2_a, decimalToBinary(sum_a));
    printf("Thap phan: %d + %d = %d\n", dec1_a, dec2_a, sum_a);

    // b) Phep tru
    int dec1_b = binaryToDecimal(bin1_b);
    int dec2_b = binaryToDecimal(bin2_b);
    int diff_b = dec1_b - dec2_b;
    printf("Phep tru b:\n");
    printf("Nhi phan: %d - %d = %d\n", bin1_b, bin2_b, decimalToBinary(diff_b));
    printf("Thap phan: %d - %d = %d\n", dec1_b, dec2_b, diff_b);
}
///////////////PHAN CODE CAU 3///////////////
// Ham in so nhi phan
void printBinary(int binary[], int bits) {
    for (int i = 0; i < bits; i++) {
        printf("%d", binary[i]);
    }
    printf("\n");
}

// Ham chuyen thap phan sang nhi phan voi so bit xac dinh
void decimalToBinaryWithBits(int num, int bits, int binary[]) {
    for (int i = bits - 1; i >= 0; i--) {
        binary[i] = (num & 1);  // Lay bit cuoi cung
        num >>= 1;  // Xet tiep bit tiep theo
    }
}

// Ham chuyen nhi phan co so bit sang thap phan
int binaryToDecimalWithBits(int binary[], int bits) {
    int decimal = 0;
    int base = 1;
    int isNegative = binary[0]; // Kiem tra bit dau tien

    if (isNegative) {
        // Lay bu 2 cho so am
        int temp[8];
        for (int i = 0; i < bits; i++) {
            temp[i] = 1 - binary[i]; // Dao bit
        }
        // Cong 1 vao bu 1
        int carry = 1;
        for (int i = bits - 1; i >= 0; i--) {
            if (temp[i] == 1 && carry == 1) {
                temp[i] = 0;
            } else if (temp[i] == 0 && carry == 1) {
                temp[i] = 1;
                carry = 0;
            }
        }
        for (int i = bits - 1; i >= 0; i--) {
            decimal += temp[i] * base;
            base *= 2;
        }
        decimal = -decimal; // Doi dau so thap phan
    } else {
        for (int i = bits - 1; i >= 0; i--) {
            decimal += binary[i] * base;
            base *= 2;
        }
    }
    return decimal;
}

// Ham lay so bu 2
void twosComplement(int binary[], int bits) {
    int carry = 1;
    for (int i = 0; i < bits; i++) {
        binary[i] = 1 - binary[i];  // Dao bit
    }
    // Cong 1 vao bu 1
    for (int i = bits - 1; i >= 0; i--) {
        if (binary[i] == 1 && carry == 1) {
            binary[i] = 0;
        } else if (binary[i] == 0 && carry == 1) {
            binary[i] = 1;
            carry = 0;
        }
    }
}

// Cau 3: Phep tru bang so bu 2
void cau3() {
    int bits = 8;  // So bit de bieu dien so

    // Phep tru dau tien: 16 - 24
    int a1 = 16, b1 = 24;
    int bin_a1[8] = {0}, bin_b1[8] = {0};

    printf("\nCau 3:\n");

    // Chuyen sang nhi phan
    decimalToBinaryWithBits(a1, bits, bin_a1);
    decimalToBinaryWithBits(b1, bits, bin_b1);
    
    // Lay so bu 2 cua b1
    twosComplement(bin_b1, bits);

    // Cong so a voi bu 2 cua b1
    int bin_res1[8] = {0};
    int carry = 0;
    for (int i = bits - 1; i >= 0; i--) {
        int sum = bin_a1[i] + bin_b1[i] + carry;
        bin_res1[i] = sum % 2;
        carry = sum / 2;
    }

    // In ket qua nhi phan va thap phan
    printf("Phep tru 16 - 24:\n");
    printf("Nhi phan: ");
    printBinary(bin_res1, bits);
    int result1 = binaryToDecimalWithBits(bin_res1, bits);
    printf("Thap phan: %d\n", result1);

    // Phep tru thu hai: -134 - (-99)
    int a2 = -134, b2 = -99;
    int bin_a2[8] = {0}, bin_b2[8] = {0};

    // Chuyen a2 va b2 sang nhi phan co dau
    decimalToBinaryWithBits(a2, bits, bin_a2);
    decimalToBinaryWithBits(b2, bits, bin_b2);

    // Lay so bu 2 cua b2
    twosComplement(bin_b2, bits);

    // Cong a2 voi bu 2 cua b2
    int bin_res2[8] = {0};
    carry = 0;
    for (int i = bits - 1; i >= 0; i--) {
        int sum = bin_a2[i] + bin_b2[i] + carry;
        bin_res2[i] = sum % 2;
        carry = sum / 2;
    }

    // In ket qua nhi phan va thap phan
    printf("\nPhep tru -134 - (-99):\n");
    printf("Nhi phan: ");
    printBinary(bin_res2, bits);
    int result2 = binaryToDecimalWithBits(bin_res2, bits);
    printf("Thap phan: %d\n", result2);
}


///////////////PHAN CODE CAU 4///////////////
// Chuyen so thap phan sang ma BCD
void decimalToBCD(int dec, int bcd[12]) {
    int i = 11;
    while (dec > 0) {
        int digit = dec % 10;  // Lay tung chu so thap phan
        for (int j = 0; j < 4; j++) {
            bcd[i--] = digit % 2;  // Chuyen tung chu so thanh nhi phan (4 bit)
            digit = digit / 2;
        }
        dec = dec / 10;
    }

    // Dien cac bit 0 vao cac bit con lai (neu co)
    while (i >= 0) {
        bcd[i--] = 0;
    }
}

// Ham in ma BCD
void printBCD(int bcd[12]) {
    for (int i = 0; i < 12; i++) {
        printf("%d", bcd[i]);
        if ((i + 1) % 4 == 0) printf(" ");  // Cu 4 bit thi them khoang trong
    }
    printf("\n");
}

// Cau 4: Chuyen doi thap phan sang ma BCD va cong
void cau4() {
    int dec1 = 135;
    int dec2 = 265;
    int bcd1[12] = {0}, bcd2[12] = {0};

    printf("\nCau 4:\n");

    // Chuyen doi thap phan sang BCD
    decimalToBCD(dec1, bcd1);
    decimalToBCD(dec2, bcd2);

    printf("Ma BCD cua %d: ", dec1);
    printBCD(bcd1);

    printf("Ma BCD cua %d: ", dec2);
    printBCD(bcd2);

    // Thuc hien phep cong
    int sum = dec1 + dec2;
    int bcdSum[12] = {0};
    decimalToBCD(sum, bcdSum);

    printf("Tong %d + %d trong BCD: ", dec1, dec2);
    printBCD(bcdSum);
}

int main() {
    cau2();
    cau3();
    cau4();
    return 0;
}
