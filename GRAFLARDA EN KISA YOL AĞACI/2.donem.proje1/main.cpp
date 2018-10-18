#include <iostream>
#include <math.h>
#include <allegro.h>
using namespace std;
class koordinatlar
{
public:
    int x;
    int y;
};
class dugum_iliski
{
public:
    int ilk_d;
    int ikinci_d;
    int uzaklik;
};

int main()
{
    int d_say,i,x,y,j;
    char matris[20][20];
    int dugum=0;
    koordinatlar dizi[400];
    dugum_iliski iliski[80200];
    for(i=0;i<20;i++){
        for(j=0;j<20;j++){
            matris[i][j]='.';
        }
    }
    while(1){
      cout<<"Kac tane dugum gireceksiniz? ";
      cin>>d_say;
      if(d_say>400)
            cout<<"En fazla 400 dugum girebilirsiniz. Tekrar giris yapiniz:\n";
      else
           break;
    }
    i=0;
    while(i<d_say){
        cout<<i+1<<". dugumun x koordinati: ";
        cin>>x;
        if(x>19){
            cout<<"En fazla 19 girebilirsiniz.\n";
            continue;
        }
        cout<<i+1<<". dugumun y koordinati: ";
        cin>>y;
          if(y>19){
            cout<<"En fazla 19 girebilirsiniz.\n";
            continue;
        }

        if(matris[y][x]!='.'){
            cout<<"Secilen koordinat dolu! Tekrar giris yapiniz:\n";
            continue;
        }
        matris[y][x]=dugum+48;
        dizi[i].x=x;
        dizi[i].y=y;
        dugum++;
        i++;
    }

    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
    clear_to_color(screen,makecol( 700, 500, 750) );
    int x1=0,y1=0;
    for(i=0;i<20;i++){
       x1=0;
       for(j=0;j<20;j++){
           textprintf_ex(screen,font,x1,y1,makecol(0,0,0),-1,"%c",matris[i][j]);
           x1+=10;
       }
       y1+=10;
    }
    int x2,y2,x3,y3;
    int renk=100;
    for(i=0;i<d_say-1;i++){
        for(j=i+1;j<d_say;j++){
                x2=dizi[i].x*10+4;
                y2=dizi[i].y*10+4;
                x3=dizi[j].x*10+4;
                y3=dizi[j].y*10+4;
            vline(screen,x3,y2,y3,renk);
            hline(screen,x2,y2,x3,renk);
            renk+=100;
        }
    }
    int a,b,q=0;
    dugum=0;
    int dugum1,d_asil=dugum;
    x1=0;
    for(i=0;i<d_say-1;i++){
        dugum=d_asil;
        dugum1=dugum+1;
        for(j=i+1;j<d_say;j++){
            a=fabs((dizi[i].x)-(dizi[j].x));
            b=fabs((dizi[i].y)-(dizi[j].y));
            iliski[q].ilk_d=dugum;
            iliski[q].ikinci_d=dugum1;
            iliski[q].uzaklik=a+b;
            q++;
            dugum1++;
        }
        d_asil++;
    }
    dugum_iliski gecici;
    if(q!=1){
        for(j=0;j<q-1;j++){  //
            for(i=0;i<q-j-1;i++){
                if(iliski[i].uzaklik>iliski[i+1].uzaklik){
                   gecici=iliski[i];
                   iliski[i]=iliski[i+1];
                   iliski[i+1]=gecici;
                }
            }
        }
    }
    textout_ex(screen, font, "DUGUMLER ARASI YOLLAR", x1, y1,makecol(0, 0, 255), -1);
    y1+=10;
    for(i=0;i<q;i++){
        textprintf_ex(screen,font,x1,y1,makecol(0,0,0),-1,"%d -> %d uzaklik : %d",iliski[i].ilk_d,iliski[i].ikinci_d,iliski[i].uzaklik);
        y1+=10;
    }
    int d_renkler[400];
    for(i=0;i<d_say;i++){
        d_renkler[i]=i;
    }
    int d1,d2,d1_renk,d2_renk;

    dugum_iliski eky_a[400];
    int eky_eleman=0;
    for(i=0;i<q;i++){//
        int cevrim = 1;
        d1=iliski[i].ilk_d;
        d2=iliski[i].ikinci_d;
        if(d_renkler[d1]==d_renkler[d2]){
            cevrim=0;
            cout<<"cevrim var eklenmedi\n";
        }
        if(cevrim==1){
            eky_a[eky_eleman]=iliski[i];
            cout<<"kenar eklendi\n";
            eky_eleman++;
        d1_renk=d_renkler[d1];
        d2_renk=d_renkler[d2];
        for(j=0;j<d_say;j++){
            if(d_renkler[j]==d2_renk){
                d_renkler[j]=d1_renk;
            }
        }
        }

    }
    int toplam=0;
    textout_ex(screen, font, "EN KISA YOL", x1, y1,makecol(0, 0, 255), -1);
    y1+=10;
    for(i=0;i<eky_eleman;i++){
        textprintf_ex(screen,font,x1,y1,makecol(0,0,0),-1,"%d -> %d uzaklik : %d",eky_a[i].ilk_d,eky_a[i].ikinci_d,eky_a[i].uzaklik);
        toplam=toplam+eky_a[i].uzaklik;
        y1+=10;
    }
    y1+=10;
    y1=0;
    x1=500;
    for(i=0;i<20;i++){
            x1=500;
       for(j=0;j<20;j++){
           textprintf_ex(screen,font,x1,y1,makecol(0,0,0),-1,"%c",matris[i][j]);
           x1+=10;
       }
       y1+=10;
    }
    x1=500;
    textprintf_ex(screen,font,x1,y1,makecol(255,0,0),-1,"Toplam Uzaklik : %d",toplam);
    y1=0;
    q=0;
    int p=0;
    for(i=0;i<eky_eleman;i++){
            p=0;
            q=0;
        for(j=0;j<eky_eleman+1;j++){
                if(eky_a[i].ilk_d==q && eky_a[i].ikinci_d==p){
                   x2=dizi[q].x*10+x1+4;
                   y2=dizi[q].y*10+y1+4;
                   x3=dizi[p].x*10+x1+4;
                   y3=dizi[p].y*10+y1+4;
                   vline(screen,x3,y2,y3,255);
                   hline(screen,x2,y2,x3,255);
                }
                if(eky_a[i].ilk_d!=q){
                    q++;
                }

                if(eky_a[i].ikinci_d!=p)
                    p++;
        }
    }
    while(!key[KEY_ESC]){}
    return 0;
}
END_OF_MAIN();
