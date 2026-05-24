#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n, m, c, c1, c1_3, c2;
double x, y, u;
char c4, OutputC[51];

typedef struct node{
	double x;
	double y;
	struct node* next;
}node;

node* makenode(double x, double y){
	node* newnode=(node*)malloc(sizeof(node));
	newnode->x=x;
	newnode->y=y;
	newnode->next=NULL;
	return newnode;
}

int size(node *head){
	int n=0;
	while(head!=NULL){
		n++;
		head=head->next;
	}
	return n;
}

void pushback(node **head, double x, double y){
	node *newnode=makenode(x,y);
	node *temp=*head;
	if(temp==NULL){
		*head=newnode;
		return;
	}
	while(temp->next!=NULL)temp=temp->next;
	temp->next=newnode;
}

void erase(node **head, int m){
	if(*head==NULL)return;
	if(m<1 || m>size(*head))return;
	node *temp=*head;
	if(m==1){
	    *head=(*head)->next;
	    free(temp);
		return;
	}
	for(int i=1; i<=m-2; i++)temp=temp->next;
	node *node_m=temp->next;
	temp->next=node_m->next;
	free(node_m);
}

void eraseall(node **head){
	if(*head==NULL)return;
	node *temp;
	while(*head!=NULL){
		temp=*head;
		*head=(*head)->next;
		free(temp);
	}
}

void title(){
    system("cls");
    printf("\n                        XAC DINH TAP CAC DIEM TREN DUONG CONG BEZIER THEO THUAT TOAN DE CASTELJAU\n");
    printf("________________________________________________________________________________________________________________________\n");
    printf("\n HO VA TEN: NGUYEN HAI NAM\n");
    printf(" MSSV: 102250347\n");
    printf(" GVHD: NGUYEN TAN KHOI\n");
    printf("________________________________________________________________________________________________________________________\n");
}

void pause1(){
	printf("\n\t\t(Nhan phim bat ky de tiep tuc...)");
    system("pause>nul");
}

void pause2(){
	printf("\n\t\t<<<!>>> Khong hop le, vui long nhan phim bat ky de nhap lai!...\n");
	system("pause>nul");
}

void xuatP(node *head){
	printf("\n\t\t Cac diem dieu khien hien tai:\n\n");
	if(head==NULL){
		printf("\t\t<<<!>>> Khong co diem nao!\n\n");
		return;
	}
	for(int i=0; head!=NULL; i++){
		printf("\t\t P%d(%lg,%lg)\n", i, head->x, head->y);
		head=head->next;
	}
	printf("\n");
}

void nhapluachon(int *c){
	if(scanf("%d", c)!=1 || getchar()!='\n'){
		while(getchar()!='\n');
		*c=-1;
	}
}

void sodiemdk(int *n){
	printf("\n\t\t Nhap so luong diem dieu khien (nhap 0 de huy): "); 
	while(1){
	    if(scanf("%d", n)!=1 || *n<0 || getchar()!='\n'){
	        printf("\n\t\t<<<!>>> Vui long nhap mot so nguyen duong! Nhap lai so luong diem dieu khien (nhap 0 de huy): ");
		    while(getchar()!='\n');
        }
	    else break;
    }
}

void nhapfile(node **head, char InputP[]){
	FILE *f;
	f=fopen(InputP, "r");
	if(f==NULL){
		printf("\n\t\t<<<!>>> File khong ton tai! Vui long tao file!\n");
		return;
	}
	int n_f;
	if(fscanf(f, "%d", &n_f)!=1 || n_f<=0)printf("\n\t\t<<<!>>> Du lieu trong file cua so luong diem dieu khien khong dung! Vui long chac chan rang dong dau tien la mot so nguyen duong!\n");
	else{
		int flag=1;
		for(int i=0; i<n_f; i++){
			double x_f, y_f;
			if(fscanf(f, "%lg %lg", &x_f, &y_f)==2)pushback(head, x_f, y_f);
            else{
			    printf("\n\t\t<<<!>>> File bi thieu toa do, chi doc duoc %d/%d diem! Da dung doc!\n", i, n_f);
			    flag=0;
			    break;
			}
		}
		if(flag)printf("\n\t\t-> Da nhap thanh cong tat ca diem dieu khien tu file %s\n", InputP);
    }
	fclose(f);
}

void deCasteljau(node *head, double u){
	int n=size(head)-1;
	double **xP=(double**)malloc((n+1)*sizeof(double*));
    double **yP=(double**)malloc((n+1)*sizeof(double*));
    for(int k=0; k<=n; k++){
        xP[k]=(double*)malloc((n+1)*sizeof(double));
        yP[k]=(double*)malloc((n+1)*sizeof(double));
    }
	node *temp=head;
	for(int i=0; i<=n; i++){
		xP[0][i]=temp->x;
		yP[0][i]=temp->y;
		temp=temp->next;
	}
	printf("\n\t\t------------- u = %.2lf -------------\n", u);
	for(int k=1; k<=n; k++){
		printf("\n\t\t Buoc %d:\n", k);
		for(int i=0; i<=n-k; i++){
			xP[k][i]=(1-u)*xP[k-1][i]+u*xP[k-1][i+1];
			yP[k][i]=(1-u)*yP[k-1][i]+u*yP[k-1][i+1];
			printf("\t\t  P[%d][%d]=(1-%lg)*P[%d][%d]+%lg*P[%d][%d]=(%lg,%lg)\n", k, i, u, k-1, i, u, k-1, i+1, xP[k][i], yP[k][i]);
		}
	}
	printf("\n\t\t-> C(%lg)=(%lg,%lg)\n", u, xP[n][0], yP[n][0]);
	for(int k=0; k<=n; k++){
        free(xP[k]);
        free(yP[k]);
    }
    free(xP); free(yP);
}

void xuatfile(node *head, char OutputC[]){
	if(head==NULL)return;
	FILE *f;
	f=fopen(OutputC, "w");
	if(f==NULL){
		printf("\n\t\t<<<!>>> Khong the tao hoac mo file!\n");
		return;
	}
	int n=size(head)-1;
    double **xP=(double**)malloc((n+1)*sizeof(double*));
    double **yP=(double**)malloc((n+1)*sizeof(double*));
    for(int k=0; k<=n; k++){
        xP[k]=(double*)malloc((n+1)*sizeof(double));
        yP[k]=(double*)malloc((n+1)*sizeof(double));
    }
    for(int j=0; j<=50; j++){
		double u=(double)j/50;
		node *temp=head;
	    for(int i=0; i<=n; i++){
		    xP[0][i]=temp->x;
		    yP[0][i]=temp->y;
		    temp=temp->next;
	    }
	    for(int k=1; k<=n; k++){
		    for(int i=0; i<=n-k; i++){
			    xP[k][i]=(1-u)*xP[k-1][i]+u*xP[k-1][i+1];
			    yP[k][i]=(1-u)*yP[k-1][i]+u*yP[k-1][i+1];
            }
        }
        fprintf(f,"C(%.2lf) = (%lg, %lg)\n", u, xP[n][0], yP[n][0]);
    }
    fclose(f);
    printf("\n\t\t-> Da xuat thanh cong ket qua 51 diem C(u) ra file %s!\n", OutputC);
    for(int k=0; k<=n; k++){
        free(xP[k]);
        free(yP[k]);
    }
    free(xP); free(yP);
}

void yesno(char *yn){
	while(1){
		if(scanf(" %c", yn)!=1 || (*yn!='Y' && *yn!='y' && *yn!='N' && *yn!='n') || getchar()!='\n'){
			printf("\n\t\t<<<!>>> Khong hop le! Vui long nhap lai (Y/N): ");
			while(getchar()!='\n');
		}
		else break;
	}
}

void case4(node *head){
	title();
	printf("\n\t\t=========================================================================================\n");
    printf("\t\t||                               4. KET QUA DE CASTELJAU                               ||\n");
    printf("\t\t=========================================================================================\n");
	if(head!=NULL){
		for(int i=0; i<=50; i++){
			u=(double)i/50;
			deCasteljau(head,u);  
		}
		printf("\n\t\t------------------------------------------------------------------------\n");
		printf("\n\t\t Luu cac toa do vao file? (Y/N): ");
		yesno(&c4);
		if(c4=='Y' || c4=='y'){
			printf("\n\t\t Nhap ten file muon luu toa do (Toi da 50 ki tu): ");
			scanf("%50s", OutputC);
			while(getchar()!='\n');
			xuatfile(head,OutputC);
		}
	}
	else printf("\n\t\t<<<!>>> Chua co diem dieu khien nao!\n");
	pause1();
}

void shortcut(node *head){
	if(head==NULL)return;
	char c_decas;
	printf("\n\t\t Ban co muon chay thuat toan de Casteljau voi bo diem nay ngay bay gio? (Y/N): ");
	yesno(&c_decas);
	if(c_decas=='Y' || c_decas=='y')case4(head);
	else pause1();
}

void case0(){
	title();
	printf("\n\t\t=========================================================================================\n");
    printf("\t\t||                                0. HUONG DAN SU DUNG                                 ||\n");
    printf("\t\t=========================================================================================\n");
	printf("\t\t  - Buoc 1: Chon [1] de them diem dieu khien (random, nhap tay hoac tu file).\n");
	printf("\t\t  - Buoc 2: Chon [2] hoac [3] de xoa diem neu co sai sot hoac kiem tra cac diem hien tai\n\t\t neu can.\n");
	printf("\t\t  - Buoc 3: Chon [4] de chuong trinh chay thuat toan de Casteljau.\n");
	printf("\t\t  - Buoc 4: Nhap Y de luu toa do ra file khi chuong trinh hien thong bao.\n\n");
	printf("\t\t  * LUU Y 1: Khi doc file input, dong dau tien cua file bat buoc phai la 1 so nguyen\n\t\t duong, chinh la so luong diem.\n");
	printf("\t\t  * LUU Y 2: Co the skip cac buoc o giua va chay luon thuat toan de Casteljau ngay sau\n\t\t buoc 1, neu trong luc them diem khong co sai sot nao\n");
	printf("\t\t-----------------------------------------------------------------------------------------\n");
	pause1();
}

node* case1(node *head){
	do{
    	title();
		printf("\n\t\t=========================================================================================\n");
        printf("\t\t||                                1. THEM DIEM DIEU KHIEN                              ||\n");
        printf("\t\t=========================================================================================\n");
		printf("\t\t  [1] Sinh diem dieu khien ngau nhien\n");
		printf("\t\t  [2] Nhap diem dieu khien tu ban phim\n");
		printf("\t\t  [3] Nhap diem dieu khien tu file co san\n");
		printf("\t\t  [4] Quay lai\n");
		printf("\t\t-----------------------------------------------------------------------------------------\n");
		printf("\t\t Nhap lua chon: ");
		nhapluachon(&c1);
		if(c1==1){
			sodiemdk(&n);
			if(n==0)pause1();
			else{
				for(int i=0; i<n; i++){
					x=(rand()%1000)/10.0;
					y=(rand()%1000)/10.0;
					pushback(&head,x,y);
				}
				printf("\n\t\t-> Da sinh ngau nhien %d diem:\n", n);
				xuatP(head);
                shortcut(head);
			}
		}
		else if(c1==2){
			sodiemdk(&n);
			if(n==0)pause1();
			else{
				int sizehientai=size(head);
				for(int i=0; i<n; i++){
					printf("\n\t\t  + Nhap diem dieu khien P%d: ", sizehientai+i);
					while(1){
					    if(scanf("%lg %lg", &x, &y)!=2 || getchar()!='\n'){
                            printf("\t\t<<<!>>> Toa do khong hop le! Vui long nhap lai P%d: ", sizehientai+i);
                            while(getchar()!='\n');
                        }
                        else break;
                    }
					pushback(&head,x,y);
				}
				printf("\n\t\t-> Da nhap thanh cong %d diem!\n\n", n);
				shortcut(head);
			}
		}
		else if(c1==3){
			do{
				title();
				printf("\n\t\t=========================================================================================\n");
                printf("\t\t||                                1.3. THEM BO DU LIEU                                 ||\n");
                printf("\t\t=========================================================================================\n");
				printf("\t\t  [1] Nhap diem dieu khien voi bo du lieu nho (n=3)\n");
				printf("\t\t  [2] Nhap diem dieu khien voi bo du lieu vua phai (n=25)\n");
				printf("\t\t  [3] Nhap diem dieu khien voi bo du lieu lon (n=100)\n");
				printf("\t\t  [4] Quay lai\n");
				printf("\t\t-----------------------------------------------------------------------------------------\n");
				printf("\t\t Nhap lua chon: ");
				nhapluachon(&c1_3);
				if(c1_3>=1 && c1_3<=3){
					if(c1_3==1)nhapfile(&head,"InputP_A.txt");
					else if(c1_3==2)nhapfile(&head,"InputP_B.txt");
					else if(c1_3==3)nhapfile(&head,"InputP_C.txt");
					shortcut(head);
                    }
				else if(c1_3==4)break;
				else pause2();
			}while(c1_3!=4);
		}
	    else if(c1==4)break;
		else pause2();
	}while(c1!=4);
	return head;
}

node* case2(node *head){
    do{
		title();
		printf("\n\t\t=========================================================================================\n");
        printf("\t\t||                               2. XOA DIEM DIEU KHIEN                                ||\n");
        printf("\t\t=========================================================================================\n");
        printf("\t\t  [1] Xoa mot diem dieu khien\n");
		printf("\t\t  [2] Xoa tat ca cac diem dieu khien\n");
		printf("\t\t  [3] Quay lai\n");
		printf("\t\t-----------------------------------------------------------------------------------------\n");
		printf("\t\t Nhap lua chon: ");
		nhapluachon(&c2);
		if(c2==1){
			if(head==NULL){
				printf("\n\t\t<<<!>>> Khong co diem dieu khien nao de xoa!\n");
				pause1();
			}
			else{
				int sizehientai=size(head);
				printf("\n");
				xuatP(head);
				printf("\n\t\t Xoa diem dieu khien: P");
				while(1){
					if(scanf("%d", &m)!=1 || getchar()!='\n'){
						printf("\n\t\t<<<!>>> Khong hop le! Vui long nhap lai diem dieu khien can xoa: P");
						while(getchar()!='\n');
					}
					else if(m<0 || m>=sizehientai)printf("\n\t\t<<<!>>> Khong ton tai diem dieu khien P%d! Vui long nhap lai diem dieu khien can xoa: P", m);
					else break;
				}
				erase(&head,m+1);
				printf("\n\t\t-> Da xoa thanh cong P%d!\n\n", m);
				pause1();
			}
		}
		else if(c2==2){
			if(head==NULL){
				printf("\n\t\t<<<!>>> Khong co diem dieu khien nao de xoa!\n");
				pause1();
			}
			else{
				eraseall(&head);
				printf("\n\t\t-> Da quet sach tat ca cac diem dieu khien\n");
				pause1();
			}
		}
		else if(c2==3)break;
		else pause2();
	}while(c2!=3);	
	return head;
}

void case3(node *head){
	title();
	printf("\n\t\t=========================================================================================\n");
    printf("\t\t||                       3. DANH SACH DIEM DIEU KHIEN HIEN TAI                         ||\n");
    printf("\t\t=========================================================================================\n");
	xuatP(head);
	pause1();
}

void case5(){
	title();
	printf("\n\n\n\t\t=========================================================================================\n");
    printf("\t\t||                              CHUONG TRINH DA KET THUC!                              ||\n");
    printf("\t\t=========================================================================================\n\n\n");
}

int main(){
	node *head=NULL;
	srand(time(NULL));
	do{
		title();
		printf("\n\t\t=========================================================================================\n");
        printf("\t\t||                                     MENU CHINH                                      ||\n");
        printf("\t\t=========================================================================================\n");
        printf("\t\t  [0] Huong dan su dung\n");
		printf("\t\t  [1] Them cac diem dieu khien\n");
	    printf("\t\t  [2] Xoa cac diem dieu khien\n");
	    printf("\t\t  [3] Xuat ra man hinh cac diem dieu khien hien tai\n");
	    printf("\t\t  [4] Chay thuat toan de Casteljau\n");
	    printf("\t\t  [5] Ket thuc chuong trinh\n");
	    printf("\t\t-----------------------------------------------------------------------------------------\n");
		printf("\t\t Nhap lua chon: ");
	    nhapluachon(&c);
	    printf("\n");
		switch(c){
			case 0:
			    case0();
	            break;
			case 1:
				head=case1(head);
				break;
			case 2:
			    head=case2(head);
			    break;
			case 3:
				case3(head);
			    break;
			case 4:
				case4(head);
				break;
			case 5:
			    case5();
				break;	
			default:
			    pause2();
		}	 
	}while(c!=5);
	return 0;
}