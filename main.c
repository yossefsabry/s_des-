// I THINK I GNOE REGERT THIS

/**
so what is the steps for s-des
1. key genrate key for encription --first
    - p10(k) == A
    - lshift(A)
    - p8(lshift(A)) - genearte key 1
    # for key 2 
    - lshift2(A) # shifting for 2
    - p8(lshift(A))
    - genearte key 2
**/

#include <stdio.h>
#include <stdlib.h>
#include "des_operation/Sbox_operation.h"
#include "helpers/swapping_operation.h"
#include "structs.h"
#include "helpers/shifting.h"
#include "helpers/spliting.h"
#include "des_operation/pn.h"
#include "des_operation/xor_operation.h"


int main() {

    // starting with define the matrix for p10 and p8 and p4
    int p10[10] = {3,5,2,7,4,10,1,9,8,6};
    int p8[8] = {6, 3, 7, 4, 8, 5, 10, 6};
    int p4[4] = {2, 4, 3, 1};
    int Ip[8] = {2, 6, 3, 1, 4, 8, 5, 7};
    int Ep[8] = {4, 1, 2, 3, 2, 3, 4, 1};
    int Ip_1[8] = {4, 1, 3, 5, 7, 2, 8, 6};

    int s_box1[4][4] = {
        {1, 0, 3, 2},
        {3, 2, 1, 0},
        {0, 2, 1, 3},
        {3, 1, 3, 2}
    };

    int s_box2[4][4] = {
        {0, 1, 2, 3},
        {2, 0, 1, 3},
        {3, 0, 1, 0},
        {2, 1, 0, 3}
    };

    // main encryption text and key
    char plain_text[8+1] = "00101000";
    char main_key[10+1] = "1100011110";

    // starting with p10
    int size_of_p10 = sizeof(p10) / sizeof(p10[0]);
    char* p10_value = pn_operation(main_key, p10, size_of_p10);

    printf("===========\n");
    printf("the value for p10: %s\n", p10_value);
    printf("===========\n");

    char *key_one;
    char *key_two;

    // for spliting the p10_value
    split_array sp_array = spliting(p10_value, sizeof(p10_value) + 2);
    printf("after spliting left: %s\n", sp_array.left_array);
    printf("after spliting right: %s\n", sp_array.right_array);
    printf("===========\n");


    // for - lshift(A)
    sarr s_arr = shifting(sp_array, 1);
    printf("the value for shifted array: %s\n", s_arr.s_arr);
    printf("===========\n");

    // - p8(lshift(A)) - genearte key 1
    int size_of_p8 = sizeof(p8) / sizeof(p8[0]);
    key_one  = pn_operation(s_arr.s_arr, p8, size_of_p8);
    printf("key one: %s\n", key_one);

    // starting for key2 now
    // FIX PROBLEM IN FIX  SHIFTING BY 2
    s_arr = shifting(sp_array, 2);
    printf("shifited 2 value: %s\n", s_arr.s_arr);

    key_two  = pn_operation(s_arr.s_arr, p8, size_of_p8);
    printf("key two: %s\n", key_two);
    printf("===========\n");

    // getting ip from Plain_text
    int size_ip = sizeof(Ip)/ sizeof(Ip[0]);
    char* ip = pn_operation(plain_text, Ip, size_ip);
    printf("ip value : %s\n", ip);
    printf("===========\n");

    // spliting the ip to right andd left part
    split_array ip_array = spliting(ip, size_ip);
    printf("after spliting left: %s\n", ip_array.left_array);
    printf("after spliting right: %s\n", ip_array.right_array);
    printf("===========\n");


    // applaying EP on R hand side of ip_array
    int size_of_ep = sizeof(Ep) / sizeof(Ep[0]);
    char *Ep_R = pn_operation(ip_array.right_array, Ep, size_of_ep);
    printf("Ep(R) value : %s\n", Ep_R);
    printf("===========\n");

    // making a xor with the first key and Ep_R
    char *results = xor_operation(key_one, Ep_R);
    printf("the value from xor key one and Ep_r: %s\n", results);
    printf("===========\n");

    // making a Sbox operation
    char* new_value = Sbox_operation(results, s_box1, s_box2);
    printf("value of sbox: %s\n", new_value);
    printf("===========\n");


    // p4 on sbox
    int size_of_p4 = sizeof(p4) / sizeof(p4[0]);
    char *sbox_p4 = pn_operation(new_value, p4, size_of_p4);
    printf("sbox p4 value : %s\n", sbox_p4);
    printf("===========\n");

    // making a xor with the sbox_p4, left side split of plain_text
    char* sbox_larr = xor_operation(sbox_p4, ip_array.left_array);
    printf("the value from xor sbox p4, left side plain_text: %s\n",
           sbox_larr);
    printf("===========\n");

    char* round_one = swapping(sbox_larr, ip_array.right_array);
    printf("==> the value for round one: %s\n", round_one);
    printf("===========\n");
    printf("==== starting round two ====\n");

    /*char username[20] = "yossef";*/
    /*char *name2 =  "sabry";*/
    /*strcat(username, name2);*/
    /*printf("usernmae: %s\n", username);*/

    free(p10_value);
    free(results);
    free(Ep_R);
    free(ip);
    free(new_value);
    free(sbox_p4);
    free(key_one);
    free(key_two);

    return 0;
}
