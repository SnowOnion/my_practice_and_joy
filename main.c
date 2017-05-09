#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>
#include<float.h>

#define max(a,b) a>b?a:b

struct point{
    double x;
    double y;
    double w;
    double new_x;
    double new_y;
};

struct point **list;

double rouding(double a){
    int  b = a * 1000;
    int c = b / 10 * 10;
    if(b - c >= 5){
        b += 10;
    }
    b = b / 10;
    return b / 100.0;
}

int compare_x(const void *a, const void *b){
    //printf("sssss\n");
    //printf("%lf, %lf\n", (*(struct point **)a)->new_x, (*(struct point **)b)->new_x);
    //printf("%lf\n", (*(struct point **)a)->new_x - (*(struct point **)b)->new_x);
    //printf("sssss\n");
    //if((*(struct point **)a)->new_x - (*(struct point **)b)->new_x > 0){
    //res = 1;
        //}else{
    //  res = -1;
    //}
    if((*(struct point **)a)->new_x - (*(struct point **)b)->new_x > 0){
        return 1;
    }else{
        return -1;
    }
}

int compare_y(const void *a, const void *b){
    double diff;
    diff = (*(struct point **)a)->new_y - (*(struct point **)b)->new_y;
    if(diff > 0){
        return 1;
    }else{
        return -1;
    }
    //return (*(struct point **)a)->new_y > (*(struct point **)b)->new_y ? 1 : -1;
}

int compare_w(const void *a, const void *b){
    int res;
    if((*(struct point **)a)->w > (*(struct point **)b)->w){
        res = -1;
    }else if((*(struct point **)a)->w < (*(struct point **)b)->w){
        res = 1;
    }else{
        res = 0;
    }
    return res;
}


int main(){
    int i, j, k, flag;
    int case_length, *length_list;
    struct point **sort_w, **sort_x, **sort_y;
    double *min, c_x, c_y, x, y, w, sum;


    freopen("./B-large-practice.in","r",stdin);
    freopen("./result.out","w",stdout);


    scanf("%d", &case_length);
    i = 0;
    length_list = (int *)malloc(case_length * sizeof(int));
    list = (struct point **)malloc(case_length * sizeof(struct point *));

    while(i < case_length){
        scanf("%d", &(length_list[i]));
        list[i] = (struct point *)malloc(length_list[i] * sizeof(struct point));
        j = 0;
        while(j < length_list[i]){
            scanf("%lf %lf %lf", &x, &y, &w);
            //x = x * w;
            //y = y * w;

            list[i][j].x = x * sqrt(2) / 2 - y * sqrt(2) / 2;
            list[i][j].y = x * sqrt(2) / 2 + y * sqrt(2) / 2;
            list[i][j].w = w;

            //printf("%lf, %lf\n", list[i][j].x, list[i][j].y);

            j++;
        }
        i++;
    }

    min = (double *)malloc(case_length * sizeof(double));
    for(i = 0; i < case_length; i++){
        //solve
        sort_w = (struct point **)malloc(length_list[i] * sizeof(struct point *));
        for(k = 0; k < length_list[i]; k++){
            sort_w[k] = &(list[i][k]);
        }
        qsort(sort_w, length_list[i], sizeof(sort_w[0]), compare_w);


        flag = 0;
        for(k = 0; k < length_list[i]; k++){

            c_x = sort_w[k]->x;
            c_y = sort_w[k]->y;

            for(j = 0; j < length_list[i]; j++){
                list[i][j].new_x = (list[i][j].x - c_x) * list[i][j].w;
                list[i][j].new_y = (list[i][j].y - c_y) * list[i][j].w;
            }

            sort_x = (struct point **)malloc(length_list[i] * sizeof(struct point *));
            for(j = 0; j < length_list[i]; j++){
                sort_x[j] = &(list[i][j]);
            }
            qsort(sort_x, length_list[i], sizeof(sort_x[0]), compare_x);

            sort_y = (struct point **)malloc(length_list[i] * sizeof(struct point *));
            for(j = 0; j < length_list[i]; j++){
                sort_y[j] = &(list[i][j]);
            }
            qsort(sort_y, length_list[i], sizeof(sort_y[0]), compare_y);


            if((sort_x[length_list[i] / 2]->new_x == 0 || sort_x[(length_list[i] - 1) / 2]->new_x == 0) && (sort_y[length_list[i] / 2]->new_y == 0 || sort_y[(length_list[i] - 1) / 2]->new_y == 0)){
                c_x = 0.00;
                c_y = 0.00;
                flag = 1;
                free(sort_x);
                free(sort_y);
                break;
            }
            free(sort_x);
            free(sort_y);

        }

        if(flag == 0){
            c_x = sort_x[(length_list[i] - 1) / 2]->new_x;
            c_y = sort_y[(length_list[i] - 1) / 2]->new_y;
        }

        sum = 0.0;
        for(j = 0; j < length_list[i]; j++){
            if((list[i][j].new_x - c_x > 0 && list[i][j].new_y - c_y> 0) || (list[i][j].new_x - c_x < 0 && list[i][j].new_y - c_y < 0)){
                sum += fabs((list[i][j].new_x - c_x + list[i][j].new_y - c_y) / 2 * sqrt(2));
            }else{
                sum += fabs((list[i][j].new_x - c_x - list[i][j].new_y + c_y) / 2 * sqrt(2));
            }
        }
        min[i] = rouding(sum);
        free(sort_w);

    }

    //print
    for(i = 0; i < case_length; i++){
        printf("Case #%d: %lf\n", i + 1, min[i]);
    }


    /*
    //input test
    for(i = 0; i < case_length; i++){
        for(j = 0; j < length_list[i]; j++){
            printf("%lf, %lf, %lf\n", list[i][j].x, list[i][j].y, list[i][j].w);
        }
        printf("\n");
    */
    
    /*

    */

    fclose(stdin);
    fclose(stdout);
    return 0;
}
