#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#define FPS 30

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
  SDL_Rect* clip = NULL ;  
    
    //Holds offsets
    SDL_Rect offset;
    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

 
int main ()
{
	topo:;
	
	int i;
    int jogoRodando = 0, jogodRodando =0, teclaDireita = 0, teclaEsquerda = 0, teclacima = 0,
    teclabaixo = 0, pulo = 0, pulobaixo=0,pulocima=0, pulopara=0;
    
    //variaveis para pontuação ( manipulação do arquivo)
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int pt;
    
    char recorde1 [5];
    char recorde2 [5];
    char recorde3 [5];
    char recorde1d [5];
    char recorde2d [5];
    char recorde3d [5];
    
    int poder = 0;//ativa poder
    int tpoder =0; //"tempo" do poder
    int acaba = 0;//ativa tiro
   
   
    int score = 10000; //decresce
    char cscore [5];//score em string 
    
    int credito = 0;
    int abertura =0;
    int recorde = 0;
    int inicio =1;
    int fim = 0;
    int sai = 0;
    int escreve=0;//escreve recorde
    int escreved=0;
    
    int contador =0;
    
    FILE *arquivo = NULL;
    FILE *arquivo2 = NULL;
    FILE *arquivod = NULL;
    FILE *arquivo2d = NULL;
    
    
    
    
    //Inicializar o SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    //carrega a imagem
    SDL_Surface *abertura1 = IMG_Load("abertura1.png");
    SDL_Surface *abertura2 = IMG_Load("abertura2.png");
    SDL_Surface *abertura3 = IMG_Load("abertura3.png");
    SDL_Surface *abertura4 = IMG_Load("abertura4.png");
    
    SDL_Surface *creditos = IMG_Load("creditos.png");
    SDL_Surface *recordes = IMG_Load("recordes.png");
    
    
    SDL_Surface *tiro = IMG_Load("tiro.png");
    SDL_Surface *over = IMG_Load("over.png");//game over
    SDL_Surface *player = IMG_Load("samus.png");//direita
    SDL_Surface *transparente = IMG_Load("samusi.png");//invencivel
    SDL_Surface *background = IMG_Load("cenario.png");
    SDL_Surface *barril = IMG_Load("barril.png");
    SDL_Surface *item = IMG_Load("item.png");
    
    
    TTF_Init();//inicia fonte
    SDL_WM_SetCaption( "A.A", NULL );// nome da janela -------
    
    //variavel fonte
    TTF_Font *font = NULL;
    //surface do texto
    SDL_Surface *message = NULL;
    //surface recordes
     SDL_Surface *rec1 = NULL;
     SDL_Surface *rec2 = NULL;
     SDL_Surface *rec3 = NULL;
     SDL_Surface *rec1d = NULL;
     SDL_Surface *rec2d = NULL;
     SDL_Surface *rec3d = NULL;
  
    //carrega fonte
     font = TTF_OpenFont( "FreeMono.ttf", 28 );
     //cor da fonte--------
     SDL_Color textColor = { 255, 255, 255 };
     
    
    //carregar musica
    Mix_Music *music = NULL;
    //inicia mixer
     if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) 
    { 
		return 0; 
		} 
		//configura tela
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);

    int chao =414 , larguraFrame = 24 , alturaFrame = 46;
    int larguraTotal = 100, alturaTotal = 57;
    float passox ;
    float passoy;
    
    int enter = 0;
    
    //rect tiro ---------
    
    SDL_Rect fontet, destinot;
    fontet.x = 0;
    fontet.y = 0;
    fontet.w = 15;
    fontet.h = 15;

    destinot.x = 250;
    destinot.y = 140;
    destinot.w = 15;
    destinot.h = 15;
    
   // rect personagem -------------------------- 
    SDL_Rect fonte, destino;
    fonte.x = 0;
    fonte.y = 0;
    fonte.w = larguraFrame;
    fonte.h = alturaFrame;

    destino.x = 0;
    destino.y = chao;
    destino.w = larguraFrame;
    destino.h = alturaFrame;
  //--------------------------------
    
    // rect personagem invencivel.
    SDL_Rect fontei, destinoi;
    fontei.x = 0;
    fontei.y = 0;
    fontei.w = larguraFrame;
    fontei.h = alturaFrame;

    //destinoi.x = destino.x;
    //destinoi.y = destino.y;
    //destinoi.w = larguraFrame;
    //destinoi.h = alturaFrame;
    


//---------------------------------------------------------
      //  rect item
      
    SDL_Rect fonteitem, destinoitem;
    fonteitem.x = 0;
    fonteitem.y = 0;
    fonteitem.w = larguraFrame;
    fonteitem.h = alturaFrame;
    
    destinoitem.x = 100;
    destinoitem.y = 260;
    destinoitem.w = larguraFrame;
    destinoitem.h = alturaFrame;

       //barris
    SDL_Rect fontebarril, destinobarril;
    fontebarril.x = 0;
    fontebarril.y = 0;
    fontebarril.w = 20;
    fontebarril.h = 20;

    destinobarril.x = 100;
    destinobarril.y = 155;
    destinobarril.w = 20;
    destinobarril.h = 20;
    
 //-----------------------------------------
   
   SDL_Rect fontebarril1, destinobarril1;
    fontebarril1.x = 0;
    fontebarril1.y = 0;
    fontebarril1.w = 20;
    fontebarril1.h = 20;

    destinobarril1.x = 100;
    destinobarril1.y = 155;
    destinobarril1.w = 20;
    destinobarril1.h = 20;
    
 //-----------------------------------------
   
   SDL_Rect fontebarril2, destinobarril2;
    fontebarril2.x = 0;
    fontebarril2.y = 0;
    fontebarril2.w = 20;
    fontebarril2.h = 20;

    destinobarril2.x = 100;
    destinobarril2.y = 155;
    destinobarril2.w = 20;
    destinobarril2.h = 20;
    
 //-----------------------------------------
   
   SDL_Rect fontebarril3, destinobarril3;
    fontebarril3.x = 0;
    fontebarril3.y = 0;
    fontebarril3.w = 20;
    fontebarril3.h = 20;

    destinobarril3.x = 100;
    destinobarril3.y = 155;
    destinobarril3.w = 20;
    destinobarril3.h = 20;
    
    SDL_Event event;
    Uint8 start;
    
   while (1)
 {
  
    
    if (inicio)
  {
	 
	 
	  
	  // FECHA OUTROS LOOPS
	  fim = 0;
	  jogoRodando =0;
	  credito = 0;
	  
	  //atualiza recorde
	  arquivo = fopen("arq","r");
	  
	  //acha maior pontuação nivel facil-------------------
	  while((fscanf(arquivo,"%d\n",&pt)!=EOF))//lê pontuações até o final do arquivo
	  {
		 
		  if (pt>p1)
		  p1=pt;
	  }
	  fclose(arquivo);
	  
	  //segunda maior pontuação
	   arquivo = fopen("arq","r");
		  
		while((fscanf(arquivo,"%d\n",&pt)!=EOF))
	  {
		  
		  if ((pt>p2)&&(pt!=p1))
		  p2=pt;
	  }
	   fclose(arquivo);
	  
	    //terceira maior pontuação
	    arquivo = fopen("arq","r");
	    
	    while((fscanf(arquivo,"%d\n",&pt)!=EOF))
	  {
		  fscanf(arquivo,"%d",&pt);
		  if ((pt>p3)&&(pt!=p1)&&(pt!=p2))
		  p3=pt;
	  }
	  
	  //abre arquivo dos recordes
	   arquivo2 = fopen("arq2","w");
	   
	   fprintf (arquivo2,"%d\n",p1);
	   fprintf (arquivo2,"%d\n",p2);
	   fprintf (arquivo2,"%d\n",p3);
	   
	   //fecha arquivos
	   fclose(arquivo);
	   fclose(arquivo2);
//---------------------------------------------------------------------
        p1=0;
        p2=0;
        p3=0;
//atualiza recordes do nivel difícil -----------------------
  //atualiza recorde
	  arquivod = fopen("arqd","r");
	  
	  //acha maior pontuação nivel facil-------------------
	  while((fscanf(arquivod,"%d\n",&pt)!=EOF))//lê pontuações até o final do arquivo
	  {
		 
		  if (pt>p1)
		  p1=pt;
	  }
	  fclose(arquivod);
	  
	  //segunda maior pontuação
	   arquivod = fopen("arqd","r");
		  
		while((fscanf(arquivod,"%d\n",&pt)!=EOF))
	  {
		  
		  if ((pt>p2)&&(pt!=p1))
		  p2=pt;
	  }
	   fclose(arquivod);
	  
	    //terceira maior pontuação
	    arquivod = fopen("arqd","r");
	    
	    while((fscanf(arquivod,"%d\n",&pt)!=EOF))
	  {
		  fscanf(arquivod,"%d",&pt);
		  if ((pt>p3)&&(pt!=p1)&&(pt!=p2))
		  p3=pt;
	  }
	  
	  //abre arquivo dos recordes
	   arquivo2d = fopen("arq2d","w");
	   
	   fprintf (arquivo2d,"%d\n",p1);
	   fprintf (arquivo2d,"%d\n",p2);
	   fprintf (arquivo2d,"%d\n",p3);
	   
	   //fecha arquivos
	   fclose(arquivod);
	   fclose(arquivo2d); 
	    
//-----------------------------------------------------------------------------	  
		  
		  
	 
	  if(abertura == 0 )
		SDL_BlitSurface(abertura1,NULL, screen,NULL);
		
		 SDL_Flip( screen);
		 
           if(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT) exit(0);
	         	
	         if(event.type == SDL_KEYDOWN)
	         	 
            switch(event.key.keysym.sym)
            {
	         	case SDLK_DOWN :
	             abertura++;
	           	 break;
	           	case SDLK_UP:
	           	abertura--;
	           	break;
	           	case SDLK_x :
	           	enter = 1;
	           default:
	           break;
	           
	          }
	          
	    
	     
            
	          
	        
	     if ( abertura > 3)
	     abertura = 3;
	     if ( abertura < 0)
	     abertura =0;     
	     if (abertura == 1)
	     SDL_BlitSurface(abertura2,NULL, screen,NULL);
	     if (abertura == 2)
	     SDL_BlitSurface(abertura3,NULL, screen,NULL);
	     if (abertura==3)
	     SDL_BlitSurface(abertura4,NULL, screen,NULL);
	     
	     SDL_Flip( screen);
	     
	     if(abertura == 0 && enter == 1)
	     {
			  music = Mix_LoadMUS( "jogo.mp3" );
	  	  Mix_PlayMusic (music,-1);
			 jogoRodando=1;
	         
	     }
	     if(abertura == 1 && enter ==1)
	     { 
		  
		  music = Mix_LoadMUS( "jogo.mp3" );
	  	  Mix_PlayMusic (music,-1);
		 jogodRodando =1;
	     }
	     if(abertura == 2 && enter ==1)
	     credito = 1;
	      
	     if(abertura==3 && enter ==1)
	     recorde = 1;
	     
	          SDL_Flip( screen); 	  
	           
	           
}


    if(jogodRodando)
    
    {
		sprintf(cscore, "%d", score);//transforma score em string
		 message = TTF_RenderText_Solid( font, cscore, textColor );//printa score
		
		// music = Mix_LoadMUS( "jogo.mp3" );
	  //Mix_PlayMusic (music,-1);
		score--;  //decresce a cada iteração;
		inicio = 0;
		
		contador++; //determina tempo de invencibilidade
		
		if (tpoder>0)
		{
			tpoder--; //determina tempo de invencibilidade
		}
		
		//colisão com o item
		
		if ((destino.x > destinoitem.x) && (destino.x < (destinoitem.x + 24))
                                           
                                            &&
           (((destino.y +44) > destinoitem.y) && (destino.y < (destinoitem.y + 44)))
           
           && (poder == 0))
		{
		poder = 1;
		tpoder = 50; 
	    }
		
		
		
		
     start = SDL_GetTicks();


   if(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT) exit(0);

        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_RIGHT:
                
                       teclaDireita = 1;
                       passox =5.5;
                      
                     break;
                case SDLK_LEFT: 
                teclaEsquerda = 1;
                 passox =-5.5; 
                     break;
                     
               case SDLK_UP:
                teclacima = 1;
                passoy =5.5;                
                break;
                
               case SDLK_DOWN:
               teclabaixo =1;
               passoy = 5.5;
               break;
                case SDLK_x:
                if(pulopara>0)
                break;
                else if (pulo>0)
                break;
                else
                pulo=1;
               // pulopara=0;
                break;
                
                case SDLK_ESCAPE: jogoRodando = 0;
                     break;
                     default :
                     break;
                     
				 }
        

            }
        }
        //limitesescadas---------------------------------------
        // escada 1 --------------------------------------
         if((destino.y<413) && (destino.y>280))
                
                teclaEsquerda = 0;
                
         if((destino.y<413) && (destino.y>280))
                
                teclaDireita = 0;
         
         //escada2-------------------------------------
         if((destino.y<276) && (destino.y>140))
                
                teclaEsquerda = 0;
                
         if((destino.y<276) && (destino.y>140))
                
                teclaDireita = 0;
                
          //ultimoandar---------
          
          if (destino.y<138)
          {
			  teclaEsquerda = 0;
              teclaDireita = 0;
              
          }
     //---------------------------------------------------------           
        
        
         if (pulo>0) // sobe
         {
			 pulocima =1;
			 pulo++;
			 pulobaixo=0;
			
		 }
		 
		 
		 
		 if (pulo>25) // desce
		 {
			 pulocima=0;
			 pulopara++; 
			 pulobaixo=1;
			
         }
         
         if (pulopara>24) // zera variaveis
         
         {
			 pulocima = 0;
			 pulobaixo =0;
			 pulopara = 0;
			 pulo = 0;
			 
		 }
         
         //if (pulocima == 0 && pulobaixo == 0)
          //        pulopara = 0;
  
         
         
         if(event.type == SDL_KEYUP)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_RIGHT: teclaDireita = 0;
                                 //fonte.x = 0;
                     break;
                case SDLK_LEFT: teclaEsquerda = 0;
            //fonte.x = 66;
                     break;
                     case SDLK_UP:
                     teclacima = 0;
                     break;
                     case SDLK_DOWN:
                     teclabaixo=0;
                     break;
                    
                     default:
                     break;
            }
        }
        
        // barril 0-----------------------------------------------
        
        if ((destinobarril.x<570) &&(destinobarril.y<200))
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril.x = 0;
                destinobarril.y = destinobarril.y;
                destinobarril.x += +5;
        }
         // desce segundo andar ----------------------
         if ((destinobarril.x > 568) && (destinobarril.y <290))
         
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril.x = 0;
                destinobarril.y += 7 ;
                destinobarril.x = destinobarril.x;
        }
         // segundo andar ----------- 
        if (destinobarril.y>288 && destinobarril.x>250)
        
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril.x =0;
                destinobarril.y = destinobarril.y;
                destinobarril.x += -5;
        }
        
        if ((destinobarril.x <252) && (destinobarril.y >278) && (destinobarril.y < 430))
        
        {
			
			 SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril.x = 0;
                destinobarril.y += 7 ;
                destinobarril.x = destinobarril.x;
			 
		}
		
		if (destinobarril.y>428)
		
		{
			
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril.x = 0;
                destinobarril.y = destinobarril.y;
                destinobarril.x += -5;
		}
	//----------volta inicio	
		if ((destinobarril.x <= 0) && (destinobarril.y > 300) )
		{
			  SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril.x = 0;
                destinobarril.y = 155;
                destinobarril.x = 100;
		}
		
	//----------------------------------------------------------------	
		
	 // barril 1-----------------------------------------------
        if ( contador > 100)
        {
        if ((destinobarril1.x<570) &&(destinobarril1.y<200))
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril1.x = 0;
                destinobarril1.y = destinobarril1.y;
                destinobarril1.x += +5;
        }
        // desce segundo andar ----------------------
         
         if ((destinobarril1.x > 568) && (destinobarril1.y <290))
         
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril1.x = 0;
                destinobarril1.y += 7 ;
                destinobarril1.x = destinobarril1.x;
        }
         // segundo andar ----------- 
        if (destinobarril1.y>288 && destinobarril1.x>250)
        
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril1.x = 0;
                destinobarril1.y = destinobarril1.y;
                destinobarril1.x += -5;
        }
     
     //   desce ultimo andar -----------------
     
        if ((destinobarril1.x <252) && (destinobarril1.y >278) && (destinobarril1.y < 430))
        
        {
			
			 SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril1.x = 0;
                destinobarril1.y += 7 ;
                destinobarril1.x = destinobarril1.x;
			 
		}
	
	//ultimo andar	
		if (destinobarril1.y>428)
		
		{
			
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril1.x = 0;
                destinobarril1.y = destinobarril1.y;
                destinobarril1.x += -5;
		}
		
	// volta inicio		
		if ((destinobarril1.x <= 0) && (destinobarril1.y > 300) )
		{
			  SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril1.x = 0;
                destinobarril1.y = 155;
                destinobarril1.x = 100;
          }
		
	}
	//----------------------------------------------------------------
	
	// barril 2-----------------------------------------------
        if ( contador > 200)
        {
        if ((destinobarril2.x<570) &&(destinobarril2.y<200))
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril2.x = 0;
                destinobarril2.y = destinobarril2.y;
                destinobarril2.x += +5;
        }
         // desce segundo andar ----------------------
         if ((destinobarril2.x > 568) && (destinobarril2.y <290))
         
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril2.x = 0;
                destinobarril2.y += 7;
                destinobarril2.x = destinobarril2.x;
        }
      // segundo andar -----------  
        if (destinobarril2.y>288 && destinobarril2.x>250)
        
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril2.x = 0;
                destinobarril2.y = destinobarril2.y;
                destinobarril2.x += -5;
        }
     // desce ultimo andar   
        if ((destinobarril2.x <252) && (destinobarril2.y >278) && (destinobarril2.y < 430))
        
        {
			
			 SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril2.x = 0;
                destinobarril2.y += 7 ;
                destinobarril2.x = destinobarril2.x;
			 
		}
	//--------ultimo andar	
		if (destinobarril2.y>428)
		
		{
			
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril.x = 0;
                destinobarril2.y = destinobarril2.y;
                destinobarril2.x += -5;
		}
		
	//--------volta inicio		
		if ((destinobarril2.x <= 0) && (destinobarril2.y > 300) )
		{
			  SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril2.x = 0;
                destinobarril2.y = 155;
                destinobarril2.x = 100;
         }
		
	}
	//----------------------------------------------------------------
	
	// barril 3-----------------------------------------------
        if ( contador > 300)
        {
        if ((destinobarril3.x<570) &&(destinobarril3.y<200))
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril3.x = 0;
                destinobarril3.y = destinobarril3.y;
                destinobarril3.x += +5;
        }
        // desce segundo andar ----------------------
         
         if ((destinobarril3.x > 568) && (destinobarril3.y <290))
         
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril3.x = 0;
                destinobarril3.y += 7;
                destinobarril3.x = destinobarril3.x;
        }
         // segundo andar ----------- 
        if (destinobarril3.y>288 && destinobarril3.x>250)
        
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril3.x = 0;
                destinobarril3.y = destinobarril3.y;
                destinobarril3.x += -5;
        }
    //-------------------desce pro ultimo andar    
        if ((destinobarril3.x <252) && (destinobarril3.y >278) && (destinobarril3.y < 430))
        
        {
			
			 SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril3.x = 0;
                destinobarril3.y += 7 ;
                destinobarril3.x = destinobarril3.x;
			 
		}
	//-------------ultimo andar	
		if (destinobarril3.y>428)
		
		{
			
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril3.x = 0;
                destinobarril3.y = destinobarril3.y;
                destinobarril3.x += -5;
		}
		
	//------volta pro inicio		
		if ((destinobarril3.x <= 0) && (destinobarril3.y > 300) )
		{
			  SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril3.x = 0;
                destinobarril3.y = 155;
                destinobarril3.x = 100;
         }
		
	}
	//----------------------------------------------------------------
	
	//colisão----------------------------------------------------------------------
	
	  //barril0---------------------------------------------------------------------	
          if ((destino.x > destinobarril.x) && (destino.x < (destinobarril.x + 24))
                                           
                                            &&
           (((destino.y +24) > destinobarril.y) && (destino.y < (destinobarril.y + 20))
          
           && ((destino.y+24>destinobarril.y)) && (tpoder<1)))
           {
			   fim = 1;
               jogodRodando =0;
	       }
      //-----------------------------------------------------------------------------
      
      //barril1
     
      
      if ((destino.x > destinobarril1.x) && (destino.x < (destinobarril1.x + 24))
                                           
                                            &&
           (((destino.y +24) > destinobarril1.y) && (destino.y < (destinobarril1.y + 20))
           
           && ((destino.y+24>destinobarril.y)) && (tpoder<1)))
          {
			  fim =1;
			  jogodRodando =0;
			  	
		  }	
    //-------------------------------------------
    
    //barril2
    
    if ((destino.x > destinobarril2.x) && (destino.x < (destinobarril2.x + 24))
                                           
                                            &&
           (((destino.y +24) > destinobarril2.y) && (destino.y < (destinobarril2.y + 20))
           
            && ((destino.y+24>destinobarril.y)) && (tpoder<1)))
          
          {
          fim = 1;
           jogodRodando =0;
          
          
	      }		
   //-------------------------------------------------------------------------------------
   //barril3
   
   if ((destino.x > destinobarril3.x) && (destino.x < (destinobarril3.x + 24))
                                           
                                            &&
           (((destino.y +24) > destinobarril3.y) && (destino.y < (destinobarril3.y + 20))
            && ((destino.y+24>destinobarril.y)) && (tpoder<1)))
           {
          fim = 1;
           jogodRodando =0;
         
	      }				
    //----------------------------------------------------------------------------- 
    //movimentação    
         if (pulocima)
         {
	            SDL_Surface *aux = player;
    	        player = IMG_Load("samus.png");
    	        SDL_FreeSurface(aux);
                fonte.x = larguraFrame;
                destino.y += -1;
                destino.x = destino.x;
           }
                
                
                
	          
	          
	         if (pulobaixo)
	             {
	            SDL_Surface *aux = player;
    	        player = IMG_Load("samus.png");
    	        SDL_FreeSurface(aux);
                fonte.x = larguraFrame;
                destino.y += +1;
                destino.x = destino.x;
                
                
			    }
		// dá o tiro	  
			  if (acaba)
			  {
				SDL_Surface *aux = tiro;
    	        tiro = IMG_Load("tiro.png");
    	        SDL_FreeSurface(aux);
                fontet.x = 0;
                destinot.y = destinot.y;
                destinot.x += -5;
                
			}
			
			if (destinot.x<100)
			{
				credito=1;
				escreved = 1;
	            jogodRodando=0;
		       }	  
	           
	    
	//-------------------------	
	//ganhar-------------------------------------------------
	if (destino.x <300 && destino.y < 140 )
	{
		
		teclaEsquerda = 0;
		acaba = 1;
		
	}	 

    	 if(teclaDireita)
    {
    	SDL_Surface *aux = player;
    	player = IMG_Load("samus.png");
    	SDL_FreeSurface(aux);
        fonte.x += larguraFrame;
        destino.x += passox;
    }
    

     if(teclaEsquerda)
    {
    	SDL_Surface *aux = player;
    	player = IMG_Load("samusesquerda.png");
    	SDL_FreeSurface(aux);
        fonte.x -= larguraFrame;
        destino.x += passox;
    }
    
    //escada-------------------------------------------------------------------------
    if(teclacima)
    {   
		if (((destino.x >= 495) && (destino.x <=520) && (destino.y > 280))
		
		|| ((destino.x >= 380) && (destino.x <=410) && (destino.y < 280) && (destino.y>140) ))
		
		{
 
    	SDL_Surface *aux = player;
    	player = IMG_Load("samusesquerda.png");
    	SDL_FreeSurface(aux);
        fonte.x -= larguraFrame;
        destino.y -= passoy;
        } 
		
    }
    
    if(teclabaixo)
    
    {   
		if (((destino.x >= 495) && (destino.x <=520) && (destino.y <414))
		
		|| ((destino.x >= 380) && (destino.x <=410) && (destino.y < 277)))
		
		{
			
    	SDL_Surface *aux = player;
    	player = IMG_Load("samusesquerda.png");
    	SDL_FreeSurface(aux);
        fonte.x -= larguraFrame;
        destino.y += passoy;
        } 
		
    }
    
    
//----------------------------------------------------------------------------------------		

    if(fonte.x > larguraTotal-larguraFrame)
        fonte.x = 0;

    if(fonte.x < 0)
        fonte.x = larguraTotal-larguraFrame;

//600 eh o canto direito da tela
    if(destino.x >= 616)
    {
        destino.x = 616;
    }

    if(destino.x <= 0)
    {
      destino.x = 0;
    }

    //Blitar a imagem na tela
    //SDL_BlitSurface(player, &fonte, screen, &destino);
    SDL_BlitSurface(background, 0, screen, 0);//fundo
    
    if (tpoder>0)
    SDL_BlitSurface(transparente, &fonte, screen, &destino);//personagem invencivel;
    else 
    SDL_BlitSurface(player, &fonte, screen, &destino);//personagem
    
    //blit barril 0
    SDL_BlitSurface(barril, &fontebarril, screen, &destinobarril);
    // blit barril 1
    if (contador > 100 )
    SDL_BlitSurface(barril, &fontebarril1, screen, &destinobarril1);
    // blit barril 2
    if (contador > 200 )
    SDL_BlitSurface(barril, &fontebarril2, screen, &destinobarril2);
    // blit barril 3
    if (contador > 300 )
    SDL_BlitSurface(barril, &fontebarril3, screen, &destinobarril3);
    //blit item
    if ( poder == 0)
     SDL_BlitSurface(item, &fonteitem, screen, &destinoitem);
     //blit tiro
     if(acaba)
     SDL_BlitSurface(tiro, &fontet, screen, &destinot);
     
      apply_surface( 300, 100, message, screen );//chama função que printa o score
    

    //Atualiza a tela
      if(1000/FPS >(SDL_GetTicks()-start))
          SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
       SDL_Flip( screen);

           if(SDL_Flip(screen) == -1)
          {
           return 1;
          }
    }      
	  
//-------------------------------------------------------------------------------------
// nivel fácil------------------------------------------------------------------------------

    if(jogoRodando)
    
    {
		sprintf(cscore, "%d", score);//transforma score em string
		 message = TTF_RenderText_Solid( font, cscore, textColor );//printa score
		inicio = 0;
		
		score--;
		
		contador++;
		
		if (tpoder>0)
		{
			tpoder--;
		}
		
		if ((destino.x > destinoitem.x) && (destino.x < (destinoitem.x + 24))
                                           
                                            &&
           (((destino.y +44) > destinoitem.y) && (destino.y < (destinoitem.y + 44)))
           
           && (poder == 0))
		{
		poder = 1;
		tpoder = 100;
	    }
	    
	    
		
		
     start = SDL_GetTicks();


   if(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT) exit(0);

        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_RIGHT:
                
                       teclaDireita = 1;
                       passox =5.5;
                     break;
                case SDLK_LEFT: 
                teclaEsquerda = 1;
                 passox =-5.5; 
                     break;
                     
               case SDLK_UP:
                teclacima = 1;
                passoy =5.5;                
                break;
                
               case SDLK_DOWN:
               teclabaixo =1;
               passoy = 5.5;
               break;
               case SDLK_x:
                if(pulopara>0)
                break;
                else if (pulo>0)
                break;
                else
                {pulo=1;
                break;}
                
                case SDLK_ESCAPE: jogoRodando = 0;
                     break;
                     default :
                     break;
                     
				 }
        

            }
        }
        //limitesescadas---------------------------------------
        // escada 1 --------------------------------------
         if((destino.y<413) && (destino.y>280))
                
                teclaEsquerda = 0;
                
         if((destino.y<413) && (destino.y>280))
                
                teclaDireita = 0;
         
         //escada2-------------------------------------
         if((destino.y<276) && (destino.y>140))
                
                teclaEsquerda = 0;
                
         if((destino.y<276) && (destino.y>140))
                
                teclaDireita = 0;
                
          //ultimoandar---------
          
          if (destino.y<138)
          {
			  teclaEsquerda = 0;
              teclaDireita = 0;
              
          }
     //---------------------------------------------------------           
        
        
         
         if (pulo>0) // sobe
         {
			 pulocima =1;
			 pulo++;
			 pulobaixo=0;
			
		 }
		 
		 
		 
		 if (pulo>25) // desce
		 {
			 pulocima=0;
			 pulopara++; 
			 pulobaixo=1;
			
         }
         
         if (pulopara>24) // zera variaveis
         
         {
			 pulocima = 0;
			 pulobaixo =0;
			 pulopara = 0;
			 pulo = 0;
			 
		 }
         
  
         
         
         if(event.type == SDL_KEYUP)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_RIGHT: teclaDireita = 0;
                                 //fonte.x = 0;
                     break;
                case SDLK_LEFT: teclaEsquerda = 0;
            //fonte.x = 66;
                     break;
                     case SDLK_UP:
                     teclacima = 0;
                     break;
                     case SDLK_DOWN:
                     teclabaixo=0;
                     break;
                    
                     default:
                     break;
            }
        }
        
        // barril 0-----------------------------------------------
        
        if ((destinobarril.x<570) &&(destinobarril.y<200))
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril.x = 0;
                destinobarril.y = destinobarril.y;
                destinobarril.x += +3;
        }
         // desce segundo andar ----------------------
         if ((destinobarril.x > 568) && (destinobarril.y <290))
         
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril.x = 0;
                destinobarril.y += 4 ;
                destinobarril.x = destinobarril.x;
        }
         // segundo andar ----------- 
        if (destinobarril.y>288 && destinobarril.x>250)
        
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril.x = 0;
                destinobarril.y = destinobarril.y;
                destinobarril.x += -3;
        }
   //---------------------------desce para o primeiro andar     
        if ((destinobarril.x <252) && (destinobarril.y >278) && (destinobarril.y < 430))
        
        {
			
			 SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril.x = 0;
                destinobarril.y += 4 ;
                destinobarril.x = destinobarril.x;
			 
		}
	//--------------------------------------------------
	//primeiro andar	
		if (destinobarril.y>428)
		
		{
			
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril.x = 0;
                destinobarril.y = destinobarril.y;
                destinobarril.x += -3;
		}
	//--------------------------------------------------
	//volta para cima---------------------------------------------
		
		if ((destinobarril.x <= 0) && (destinobarril.y > 300) )
		{
			  SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril.x = 0;
                destinobarril.y = 155;
                destinobarril.x = 100;
		}
		
	//----------------------------------------------------------------	
		
	 // barril 1-----------------------------------------------
        if ( contador > 100)
        {
        if ((destinobarril1.x<570) &&(destinobarril1.y<200))
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril1.x = 0;
                destinobarril1.y = destinobarril1.y;
                destinobarril1.x += +3;
        }
         // desce segundo andar ----------------------
         if ((destinobarril1.x > 568) && (destinobarril1.y <290))
         
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril1.x = 0;
                destinobarril1.y += 4 ;
                destinobarril1.x = destinobarril1.x;
        }
         // segundo andar ----------- 
        if (destinobarril1.y>288 && destinobarril1.x>250)
        
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril1.x = 0;
                destinobarril1.y = destinobarril1.y;
                destinobarril1.x += -3;
        }
        
        //---------------------desce para o ultimo andar
        
        if ((destinobarril1.x <252) && (destinobarril1.y >278) && (destinobarril1.y < 430))
        
        {
			
			 SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril1.x = 0;
                destinobarril1.y += 4 ;
                destinobarril1.x = destinobarril1.x;
			 
		}
		//----------------ultimo andar
		
		if (destinobarril1.y>428)
		
		{
			
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril1.x = 0;
                destinobarril1.y = destinobarril1.y;
                destinobarril1.x += -3;
		}
		
		// ---------- volta inicio
			
		if ((destinobarril1.x <= 0) && (destinobarril1.y > 300) )
		{
			  SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril1.x = 0;
                destinobarril1.y = 155;
                destinobarril1.x = 100;
          }
		
	}
	//----------------------------------------------------------------
	
	// barril 2-----------------------------------------------
        if ( contador > 200)
        {
        if ((destinobarril2.x<570) &&(destinobarril2.y<200))
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril2.x = 0;
                destinobarril2.y = destinobarril2.y;
                destinobarril2.x += +3;
        }
         // desce segundo andar ----------------------
         if ((destinobarril2.x > 568) && (destinobarril2.y <290))
         
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril2.x = 0;
                destinobarril2.y += 4 ;
                destinobarril2.x = destinobarril2.x;
        }
         // segundo andar ----------- 
        if (destinobarril2.y>288 && destinobarril2.x>250)
        
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril2.x = 0;
                destinobarril2.y = destinobarril2.y;
                destinobarril2.x += -3;
        }
        //--------desce ultimo andar
        
        if ((destinobarril2.x <252) && (destinobarril2.y >278) && (destinobarril2.y < 430))
        
        {
			
			 SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril2.x = 0;
                destinobarril2.y += 4 ;
                destinobarril2.x = destinobarril2.x;
			 
		}
		//---- ultimo andar
		if (destinobarril2.y>428)
		
		{
			
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril.x = 0;
                destinobarril2.y = destinobarril2.y;
                destinobarril2.x += -3;
		}
		
		//volta inicio	
		if ((destinobarril2.x <= 0) && (destinobarril2.y > 300) )
		{
			  SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril2.x = 0;
                destinobarril2.y = 155;
                destinobarril2.x = 100;
         }
		
	}
	//----------------------------------------------------------------
	
	// barril 3-----------------------------------------------
        if ( contador > 300)
        {
        if ((destinobarril3.x<570) &&(destinobarril3.y<200))
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril3.x = 0;
                destinobarril3.y = destinobarril3.y;
                destinobarril3.x += +3;
        }
         // desce segundo andar ----------------------
         if ((destinobarril3.x > 568) && (destinobarril3.y <290))
         
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril3.x = 0;
                destinobarril3.y += 4 ;
                destinobarril3.x = destinobarril3.x;
        }
         // segundo andar ----------- 
        if (destinobarril3.y>288 && destinobarril3.x>250)
        
        {
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril3.x = 0;
                destinobarril3.y = destinobarril3.y;
                destinobarril3.x += -3;
        }
        
        //desce ultimo andar-------------------
        if ((destinobarril3.x <252) && (destinobarril3.y >278) && (destinobarril3.y < 430))
        
        {
			
			 SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril3.x = 0;
                destinobarril3.y += 4 ;
                destinobarril3.x = destinobarril3.x;
			 
		}
		// ultimo andar
		if (destinobarril3.y>428)
		
		{
			
                SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril3.x = 0;
                destinobarril3.y = destinobarril3.y;
                destinobarril3.x += -3;
		}
		
		//volta inicio --------------
			
		if ((destinobarril3.x <= 0) && (destinobarril3.y > 300) )
		{
			  SDL_Surface *aux = barril;
    	        barril = IMG_Load("barril.png");
    	        SDL_FreeSurface(aux);
                fontebarril3.x = 0;
                destinobarril3.y = 155;
                destinobarril3.x = 100;
         }
		
	}
	//----------------------------------------------------------------
	
	//colisão----------------------------------------------------------------------
	
	  //barril0---------------------------------------------------------------------	
          if ((destino.x > destinobarril.x) && (destino.x < (destinobarril.x + 24))
                                           
                                            &&
           (((destino.y +24) > destinobarril.y) && (destino.y < (destinobarril.y + 20))
           && ((destino.y+24>destinobarril.y))
           && (tpoder<1)))
           {
			   fim = 1;
               jogoRodando =0;
	       }
      //-----------------------------------------------------------------------------
      
      //barril1
      
      if ((destino.x > destinobarril1.x) && (destino.x < (destinobarril1.x + 24))
                                           
                                            &&
           (((destino.y +24) > destinobarril1.y) && (destino.y < (destinobarril1.y + 20))
           && ((destino.y+24>destinobarril1.y)) && (tpoder<1)))
          {
			  fim =1;
			  jogoRodando =0;
			  	
		  }	
    //-------------------------------------------
    
    //barril2
    
    if ((destino.x > destinobarril2.x) && (destino.x < (destinobarril2.x + 24))
                                           
                                            &&
           (((destino.y +24) > destinobarril2.y) && (destino.y < (destinobarril2.y + 20)) 
           && ((destino.y+24>destinobarril2.y)) && (tpoder<1)))
          
          {
          fim = 1;
           jogoRodando =0;
          
          
	      }		
   //-------------------------------------------------------------------------------------
   //barril3
   
   if ((destino.x > destinobarril3.x) && (destino.x < (destinobarril3.x + 24))
                                           
                                            &&
           (((destino.y +24) > destinobarril3.y) && (destino.y < (destinobarril3.y + 20)) 
           && ((destino.y+24>destinobarril.y)) && (tpoder<1)))
           {
          fim = 1;
           jogoRodando =0;
         
	      }				
    //-----------------------------------------------------------------------------     
         if (pulocima)
         {
	            SDL_Surface *aux = player;
    	        player = IMG_Load("samus.png");
    	        SDL_FreeSurface(aux);
                fonte.x = larguraFrame;
                destino.y += -1;
                destino.x = destino.x;
           }
                
                
                
	          
	          
	         if (pulobaixo)
	             {
	            SDL_Surface *aux = player;
    	        player = IMG_Load("samus.png");
    	        SDL_FreeSurface(aux);
                fonte.x = larguraFrame;
                destino.y += +1;
                destino.x = destino.x;
                
                
			    }
	           
	    
			 

    	 if(teclaDireita)
    {
    	SDL_Surface *aux = player;
    	player = IMG_Load("samus.png");
    	transparente = IMG_Load("samusi.png");
    	SDL_FreeSurface(aux);
        fonte.x += larguraFrame;
        destino.x += passox;
    }

     if(teclaEsquerda)
    {
    	SDL_Surface *aux = player;
    	player = IMG_Load("samusesquerda.png");
    	transparente = IMG_Load("samusesquerdai.png");
    	SDL_FreeSurface(aux);
        fonte.x -= larguraFrame;
        destino.x += passox;
    }
    
    // dá o tiro	  
			  if (acaba)
			  {
				SDL_Surface *aux = tiro;
    	        tiro = IMG_Load("tiro.png");
    	        SDL_FreeSurface(aux);
                fontet.x = 0;
                destinot.y = destinot.y;
                destinot.x += -5;
                
			}
			//finaliza nível.
			if (destinot.x<100)
			{
				credito=1;
				escreve = 1;//"seleciona" a escrita no arquivo dos recordes do nivel fácil
			   jogoRodando=0;
		       }	  
    //verifica fim
    if (destino.x <300 && destino.y < 140 )
	{
		teclaDireita = 0;
		teclaEsquerda = 0;
		acaba = 1;
		
		
	}	 
    
    //escada-------------------------------------------------------------------------
    if(teclacima)
    {   
		if (((destino.x >= 495) && (destino.x <=520) && (destino.y > 280))
		
		|| ((destino.x >= 380) && (destino.x <=410) && (destino.y < 280) && (destino.y>140) ))
		
		{
 
    	SDL_Surface *aux = player;
    	player = IMG_Load("samusesquerda.png");
    	SDL_FreeSurface(aux);
        fonte.x -= larguraFrame;
        destino.y -= passoy;
        } 
		
    }
    
    if(teclabaixo)
    
    {   
		if (((destino.x >= 495) && (destino.x <=520) && (destino.y <414))
		
		|| ((destino.x >= 380) && (destino.x <=410) && (destino.y < 277)))
		
		{
			
    	SDL_Surface *aux = player;
    	player = IMG_Load("samusesquerda.png");
    	SDL_FreeSurface(aux);
        fonte.x -= larguraFrame;
        destino.y += passoy;
        } 
		
    }
    
    
//----------------------------------------------------------------------------------------		

    if(fonte.x > larguraTotal-larguraFrame)
        fonte.x = 0;

    if(fonte.x < 0)
        fonte.x = larguraTotal-larguraFrame;

//600 eh o canto direito da tela
    if(destino.x >= 616)
    {
        destino.x = 616;
    }

    if(destino.x <= 0)
    {
      destino.x = 0;
    }

    //Blitar a imagem na tela
    //SDL_BlitSurface(player, &fonte, screen, &destino);
    SDL_BlitSurface(background, 0, screen, 0);
    if (tpoder>0)
    SDL_BlitSurface(transparente, &fonte, screen, &destino);//personagem invencivel;
    else
    SDL_BlitSurface(player, &fonte, screen, &destino);
    //blit barril 0
    SDL_BlitSurface(barril, &fontebarril, screen, &destinobarril);
    // blit barril 1
    if (contador > 100 )
    SDL_BlitSurface(barril, &fontebarril1, screen, &destinobarril1);
    // blit barril 2
    if (contador > 200 )
    SDL_BlitSurface(barril, &fontebarril2, screen, &destinobarril2);
    // blit barril 3
    if (contador > 300 )
    SDL_BlitSurface(barril, &fontebarril3, screen, &destinobarril3);
    //blit item
    if (poder == 0 )
     SDL_BlitSurface(item, &fonteitem, screen, &destinoitem);
       if(acaba)
     SDL_BlitSurface(tiro, &fontet, screen, &destinot);
     
     apply_surface( 300, 100, message, screen );

    //Atualiza a tela
      if(1000/FPS >(SDL_GetTicks()-start))
          SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
       SDL_Flip( screen);

           if(SDL_Flip(screen) == -1)
          {
           return 1;
          }
  //--------------------------------------------fim nível fácil        
	  }
	  if(fim)
		
		{
			jogoRodando = 0;
			
			SDL_BlitSurface(over, 0, screen, 0);
		
           if(SDL_PollEvent(&event))
              {
	         	 if(event.type == SDL_KEYDOWN)
	           	 { 
					 sai = 1;
				  }
				
	            
	            if (sai == 1)
	            {
					goto topo;
					
			     } 
	          }
	          
	          SDL_Flip( screen);
	  
       }
	  
     if(credito)
     {
		
		 inicio = 0;
	
	     sai=0;
	   if(escreve)//grava recorde para nivel facil.-------------
	   {
		   arquivo = fopen("arq", "a");
	       fprintf (arquivo,"%s\n",cscore);
	       fclose(arquivo);
	       escreve = 0;
	    }
	   //----------------------------------------------
	   
	    if(escreved)//grava recorde para nivel dificil.-------------
	   {
		   arquivod = fopen("arqd", "a");
	       fprintf (arquivod,"%s\n",cscore);
	       fclose(arquivod);
	       escreved = 0;
	    }
	  //-------------------------------------------------- 
	    
	     	
     SDL_BlitSurface(creditos, 0, screen, 0);//fundo
      
      SDL_Flip( screen);
      if(SDL_PollEvent(&event))
       
            if(event.type == SDL_QUIT) exit(0);
              
	         	 if(event.type == SDL_KEYDOWN)
	         	 switch(event.key.keysym.sym)
	         	 {
	         	 case SDLK_x:
	         	 sai=1;
	         	 break;
	         	 
	         	 default
	         	 : break;
			     }
			     
			     if (sai == 1)
			     {
			    goto topo;
			    
			     }			     
               
              
   }  
   
    if(recorde)
     {
		
		 inicio = 0;
	
	     sai=0;
	     
	     arquivo2 = fopen("arq2","r");
	     fscanf(arquivo2,"%s",recorde1);
	     fscanf(arquivo2,"%s",recorde2);
         fscanf(arquivo2,"%s",recorde3);
      
  //recordes do nivel dificil---------------------------------------------  
         arquivo2d = fopen("arq2d","r");
	     fscanf(arquivo2d,"%s",recorde1d);
	     fscanf(arquivo2d,"%s",recorde2d);
         fscanf(arquivo2d,"%s",recorde3d);
//-----------------------------
	     
	 
	     
		rec1 = TTF_RenderText_Solid( font, recorde1, textColor );//renderiza recorde
		rec2 = TTF_RenderText_Solid( font, recorde2, textColor );//renderiza recorde
		rec3 = TTF_RenderText_Solid( font, recorde3, textColor );//renderiza recorde
//---------------------------------------------dificil
        
        rec1d = TTF_RenderText_Solid( font, recorde1d, textColor );//renderiza recorde
		rec2d = TTF_RenderText_Solid( font, recorde2d, textColor );//renderiza recorde
		rec3d = TTF_RenderText_Solid( font, recorde3d, textColor );//renderiza recorde
				
	//----------------------------------------------------------  
	     	
     SDL_BlitSurface(recordes, 0, screen, 0);//fundo
     apply_surface( 150, 100, rec1, screen );
     apply_surface( 150, 150, rec2, screen );
     apply_surface( 150, 200, rec3, screen );
     //---dificil--------
     apply_surface( 400, 100, rec1d, screen );
     apply_surface( 400, 150, rec2d, screen );
     apply_surface( 400, 200, rec3d, screen );
     
     fcloseall();//fecha todos os arquivos----------------
      
      SDL_Flip( screen);
      if(SDL_PollEvent(&event))
       
            if(event.type == SDL_QUIT) exit(0);
              
	         	 if(event.type == SDL_KEYDOWN)
	         	 switch(event.key.keysym.sym)
	         	 {
	         	 case SDLK_x:
	         	 sai=1;
	         	 break;
	         	 
	         	 default
	         	 : break;
			     }
			     
			     if (sai == 1)
			     {
			    goto topo;
			    
			     }	
	}		
   
  } //fechamento do while 1 
    //Liberar imagem carregada
    SDL_FreeSurface(background);
    SDL_FreeSurface(player);
    SDL_FreeSurface(barril);
   
    //Encerra o SDL
    SDL_Quit();
    return 0;
}

