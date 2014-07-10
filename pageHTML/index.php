    <!DOCTYPE html>
    <html>

    <head>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">




      <style>
      @media (max-width: 640px) {

       /* passer tous les éléments de largeur fixe en largeur automatique */
       body, element1, element2 {
         width: auto;
         margin: 0;
         padding: 0;
       }

       /* fixer une largeur maximale  de 100 % aux éléments potentiellement problématiques */
       img, table, td, blockquote, code, pre, textarea, input, iframe, object, embed, video {
         max-width: 100%;
       }
       /* conserver le ratio des images et empêcher les débordements de boîtes dûs aux border ou padding */
       img {
         height: auto;
         -webkit-box-sizing: border-box;
         -moz-box-sizing: border-box;
         box-sizing: border-box;
       }

       /* gestion des mots longs */
       textarea, table, td, th, code, pre, samp {
         word-wrap: break-word; /* passage à la ligne forcé */
         -webkit-hyphens: auto; /* césure propre */
         -moz-hyphens: auto;
         hyphens: auto;
       }
       code, pre, samp {
         white-space: pre-wrap; /* passage à la ligne spécifique pour les éléments à châsse fixe */
       }

       /* Passer à une seule colonne (à appliquer aux éléments multi-colonnes) */
       element1, element2 {
         float: none;
         width: auto;
       }

       /* masquer les éléments superflus */
       .hide_mobile {
         display: none !important;
       }

       /* Un message personnalisé */
       body:before {
         content: "Tcomp Mobile";
         display: block;
         color: #777;
         text-align: center;
         font-style: italic;
       }
     }
div.tab
    {
    width : 40px;
    }
 

     </style>
    





     <title>TComp Command Center</title>
     <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.9.0/jquery.min.js"></script>
     <!--[if IE]><script type="text/javascript" src="excanvas.js"></script><![endif]-->

     <script src="js/jquery.knob.js"></script>
    <!--<script type="text/javascript" src="recupid.js"></script>-->
     <script>
     /*
URL = "recupid.php";
function rafraichir() {
        if (window.XMLHttpRequest) xhr = new XMLHttpRequest();
        else if (window.ActiveXObject) xhr = new ActiveXObject('Microsoft.XMLHTTP');
        else alert('JavaScript : votre navigateur ne supporte pas les objets XMLHttpRequest...');
        xhr.open('GET',URL,true);
        xhr.onreadystatechange = ajaxReponse;
        xhr.send(null);
}
 
function ajaxReponse() {
        if (xhr.readyState == 4) {
                document.getElementById("page",true).innerHTML=xhr.responseText; // ici sa s'incrute dans la div <div id="page"></div> mais peut etre <td id="page">  ... Ici c'est L'id l'important
                var timer=setTimeout("rafraichir()",2000); // rafraichie toute les 25secs
        }
}*/
function file(fichier)
{
if(window.XMLHttpRequest) // FIREFOX
xhr_object = new XMLHttpRequest();
else if(window.ActiveXObject) // IE
xhr_object = new ActiveXObject("Microsoft.XMLHTTP");
else
return(false);
xhr_object.open("GET", fichier, false);
xhr_object.send(null);
if(xhr_object.readyState == 4) return(xhr_object.responseText);
else return(false);
}
     function RefreshIMG() {
      
       setTimeout("RefreshIMG()",delay*1000); 
       recupwidth=document.documentElement.clientWidth
       if (recupwidth<800)
       {
        $('.knob').trigger('configure',{"width":100})
        $('.knob2').trigger('configure',{"width":100})
        hdiv1 = document.getElementById('secondknob');
        hdiv1.style.left="55%";
        hdiv2 = document.getElementById('boutonOK1');
        hdiv2.style.top="22%";
        hdiv2.style.left="15%";
        hdiv3 = document.getElementById('boutonOK2');
        hdiv3.style.top="0%";
        hdiv3.style.left="225%";


        hdiva = document.getElementById('f');
        hdivg = document.getElementById('l');
        hdivs = document.getElementById('s');
        hdivd = document.getElementById('r');
        hdivr = document.getElementById('re');
        hdiva.style.height="60px";
        hdivg.style.height="60px";
        hdivs.style.height="60px";
        hdivd.style.height="60px";
        hdivr.style.height="60px";
        hdiva.style.width="60px";
        hdivg.style.width="60px";
        hdivs.style.width="60px";
        hdivd.style.width="60px";
        hdivr.style.width="60px";

        hdivcom = document.getElementById('commandes');
        hdivcom2 = document.getElementById('commandes2');
        hdivcom3 = document.getElementById('commandes3');
        hdivcom.style.top="30%";
        hdivcom.style.left="40%";
        hdivcom2.style.top="40%";
        hdivcom2.style.left="19.75%";
        hdivcom3.style.top="50%";
        hdivcom3.style.left="40%";

        hdivcambou = document.getElementById('camerabouton');
        hdivcambou.style.top="95%";
        hdivcambou.style.left="28%";
        hdivcam = document.getElementById('camera');
        hdivcam.style.height="150px";
        hdivcam.style.width="150px";
        hdivcam.style.top="63%";
        hdivcam.style.left="25%";
      }
    }
    $(function($) {

      $(".knob").knob({
        change : function (value) {
                            //console.log("change : " + value);
                          },
                          release : function (value) {
                            //console.log(this.$.attr('value'));
                            console.log("release : " + value);
                          },
                          cancel : function () {
                            console.log("cancel : ", this);
                          },
                        /*format : function (value) {
                            return value + '%';
                          },*/
                          draw : function () {

                            // "tron" case
                            if(this.$.data('skin') == 'tron') {

                              this.cursorExt = 0.3;

                                var a = this.arc(this.cv)  // Arc
                                    , pa                   // Previous arc
                                    , r = 1;

                                    this.g.lineWidth = this.lineWidth;

                                    if (this.o.displayPrevious) {
                                      pa = this.arc(this.v);
                                      this.g.beginPath();
                                      this.g.strokeStyle = this.pColor;
                                      this.g.arc(this.xy, this.xy, this.radius - this.lineWidth, pa.s, pa.e, pa.d);
                                      this.g.stroke();
                                    }

                                    this.g.beginPath();
                                    this.g.strokeStyle = r ? this.o.fgColor : this.fgColor ;
                                    this.g.arc(this.xy, this.xy, this.radius - this.lineWidth, a.s, a.e, a.d);
                                    this.g.stroke();

                                    this.g.lineWidth = 2;
                                    this.g.beginPath();
                                    this.g.strokeStyle = this.o.fgColor;
                                    this.g.arc( this.xy, this.xy, this.radius - this.lineWidth + 1 + this.lineWidth * 2 / 3, 0, 2 * Math.PI, false);
                                    this.g.stroke();

                                    return false;
                                  }
                                }
                              });

    $(".knob2").knob({
      change : function (value) {
                            //console.log("change : " + value);
                          },
                          release : function (value) {
                            //console.log(this.$.attr('value'));
                            console.log("release : " + value);
                          },
                          cancel : function () {
                            console.log("cancel : ", this);
                          },
                        /*format : function (value) {
                            return value + '%';
                          },*/
                          draw : function () {

                            // "tron" case
                            if(this.$.data('skin') == 'tron') {

                              this.cursorExt = 0.3;

                                var a = this.arc(this.cv)  // Arc
                                    , pa                   // Previous arc
                                    , r = 1;

                                    this.g.lineWidth = this.lineWidth;

                                    if (this.o.displayPrevious) {
                                      pa = this.arc(this.v);
                                      this.g.beginPath();
                                      this.g.strokeStyle = this.pColor;
                                      this.g.arc(this.xy, this.xy, this.radius - this.lineWidth, pa.s, pa.e, pa.d);
                                      this.g.stroke();
                                    }

                                    this.g.beginPath();
                                    this.g.strokeStyle = r ? this.o.fgColor : this.fgColor ;
                                    this.g.arc(this.xy, this.xy, this.radius - this.lineWidth, a.s, a.e, a.d);
                                    this.g.stroke();

                                    this.g.lineWidth = 2;
                                    this.g.beginPath();
                                    this.g.strokeStyle = this.o.fgColor;
                                    this.g.arc( this.xy, this.xy, this.radius - this.lineWidth + 1 + this.lineWidth * 2 / 3, 0, 2 * Math.PI, false);
                                    this.g.stroke();

                                    return false;
                                  }
                                }
                              });
                    // Example of infinite knob, iPod click wheel
                    var v, up=0,down=0,i=0
                    ,$idir = $("div.idir")
                    ,$ival = $("div.ival")
                    ,incr = function() { i++; $idir.show().html("+").fadeOut(); $ival.html(i); }
                    ,decr = function() { i--; $idir.show().html("-").fadeOut(); $ival.html(i); };
                    $("input.infinite").knob(
                    {
                      min : 0
                      , max : 20
                      , stopper : false
                      , change : function () {
                        if(v > this.cv){
                          if(up){
                            decr();
                            up=0;
                          }else{up=1;down=0;}
                        } else {
                          if(v < this.cv){
                            if(down){
                              incr();
                              down=0;
                            }else{down=1;up=0;}
                          }
                        }
                        v = this.cv;
                      }
                    });
                  });
    function str_pad(input, pad_length, pad_string, pad_type) {
      //  discuss at: http://phpjs.org/functions/str_pad/
      // original by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
      // improved by: Michael White (http://getsprink.com)
      //    input by: Marco van Oort
      // bugfixed by: Brett Zamir (http://brett-zamir.me)
      //   example 1: str_pad('Kevin van Zonneveld', 30, '-=', 'STR_PAD_LEFT');
      //   returns 1: '-=-=-=-=-=-Kevin van Zonneveld'
      //   example 2: str_pad('Kevin van Zonneveld', 30, '-', 'STR_PAD_BOTH');
      //   returns 2: '------Kevin van Zonneveld-----'

      var half = '',
      pad_to_go;

      var str_pad_repeater = function(s, len) {
        var collect = '',
        i;

        while (collect.length < len) {
          collect += s;
        }
        collect = collect.substr(0, len);

        return collect;
      };

      input += '';
      pad_string = pad_string !== undefined ? pad_string : ' ';

      if (pad_type !== 'STR_PAD_LEFT' && pad_type !== 'STR_PAD_RIGHT' && pad_type !== 'STR_PAD_BOTH') {
        pad_type = 'STR_PAD_RIGHT';
      }
      if ((pad_to_go = pad_length - input.length) > 0) {
        if (pad_type === 'STR_PAD_LEFT') {
          input = str_pad_repeater(pad_string, pad_to_go) + input;
        } else if (pad_type === 'STR_PAD_RIGHT') {
          input = input + str_pad_repeater(pad_string, pad_to_go);
        } else if (pad_type === 'STR_PAD_BOTH') {
          half = str_pad_repeater(pad_string, Math.ceil(pad_to_go / 2));
          input = half + input + half;
          input = input.substr(0, pad_length);
        }
      }

      return input;
    }

    var delay=1 // ici 1 secondes
    var img="image"; // ici nom de l'image a recharger
    var src="page/test.jpg"
    var valeurcm
    var recupwidth
    var reso
    var ListeCommandes=new Array();
    var Tailletableau=0;
    var pidbash;
    var commandcomp=""
     function TransfertCommande(action)
    {
    document.location="cgi-bin/TransfertData.py?action="+action; 
    }
    function Start(){
      CheckCommande();
      RefreshIMG();
    }
    function CheckCommande(){

    setTimeout("CheckCommande()",delay*500);
    pidbash=file('recupid.php');
    if (Tailletableau>0)
    {
      for (i=1;i<=Tailletableau;i++)
      {
      commandcomp=commandcomp+ListeCommandes[i]+'<br>'
      }
      document.getElementById("TabCommandes").innerHTML=commandcomp;
      commandcomp=""
   /* 
      
        //ICI VERIFIER SI PROCESS DU BASH QUI ATTEND ARDUINO EST FERME
        if(pidbash===1)
        {
          Tailletableau--; //On decremente ici pour rester dans le while tant que l'arduino a pas dit OK
          // du coup on voit si on envoit la commande avec le if is_null du dessous
          var CommandToSend = ListeCommandes[1]; //On prend la valeur 1 vu que la premiere est toujours ecrite dans 1
          ListeCommandes.shift(); //Commande pour recup valeur 1 et decaler valeurs tableau
          if (CommandToSend === NULL)
          {
          }
          else
          {
          TransfertCommande(CommandToSend)
          }
        }
    */
    }
   }
    
    function Avancer()
    {
    valeurcm=$("input.knob").val();
    distancesaisie=str_pad(valeurcm,3,0,'STR_PAD_LEFT');
     Tailletableau++;
      ListeCommandes[Tailletableau]="A"+distancesaisie;
    //document.location="cgi-bin/Avancer.py";
    }
  function TournerG()
  {
  //var pidbash=<?php echo `pidof X`; ?>;
  //var pidbash=<?php echo file_exists( "/proc/".system(`pidof Xasqdq`) ); ?>;


   valeurcm=$("input.knob2").val();
   degressaisis=str_pad(valeurcm,3,0,'STR_PAD_LEFT');
   Tailletableau++;
   ListeCommandes[Tailletableau]='G'+degressaisis;

    //document.location="cgi-bin/TournerG.py";
  }
  function TournerD()
  {
  valeurcm=$("input.knob2").val();
   degressaisis=str_pad(valeurcm,3,0,'STR_PAD_LEFT');
   Tailletableau++;
   ListeCommandes[Tailletableau]='D'+degressaisis;

    //document.location="cgi-bin/TournerD.py";
  }
  function Stop()
  {
    document.location="cgi-bin/Stop.py";
  }
  function Reculer()
  {
    valeurcm=$("input.knob").val();
    distancesaisie=str_pad(valeurcm,3,0,'STR_PAD_LEFT');
   Tailletableau++;
   ListeCommandes[Tailletableau]='R'+distancesaisie;

    //document.location="cgi-bin/Reculer.py";
  }
  function ActiverCam()
  {
    alert("Ok");
    //document.location="cgi-bin/ActiverCam.py";

  }
  </script>

</head>
  <body onLoad="Start()">


 <div style="position:absolute;left:10%;top:5%">
  <input class="knob" data-min="0" data-max="150" data-angleOffset="-90" data-step="5" data-angleArc=360 value="0" data-fgColor="#ffec03" data-displayInput=true data-width="300"  data-height="300" data-thickness=".3">
</div>
<div id=secondknob style="position:absolute;left:50%;top:5%">
  <input class="knob2" data-min="0" data-max="360" data-step="10" data-angleOffset=-90 data-angleArc=360 value="0" data-displayInput=true data-width="300" data-height="300" data-thickness=".3">
</div>             
<form name="form1" method="post" action=""> 
    </div>
  </div>
  <br>
</form>
<br><br><br><br>
<div id=commandes style="position:absolute;left:35%;top:35%">
  <img src="page/forward.jpg" id="f" onmousedown="Avancer()">
  <br>
</div>
<div id=commandes2 style="position:absolute;left:27.175%;top:48%">
  <img src="page/left.jpg" id="l" onmousedown="TournerG()">
  <img src="page/stop.jpg" id="s" onmousedown="Stop()">

  <img src="page/right.jpg" id="r" onmousedown="TournerD()">
</div>
<br>
<div id=commandes3 style="position:absolute;left:35%;top:60%">
  <img src="page/reculer.jpg" id="re" onmousedown="Reculer()">
</div>
<br>
<div id=camerabouton style="position:absolute;left:35%;top:2%">
  <input type="button" id="bc" value="Activer Camera" onclick="ActiverCam()">
  <br>
</div>
<div id=camera style="position:absolute;left:31.5%;top:5%">
  <IMG id="image" name="image" src="page/test.jpg" width=256 height=256 alt="Cette image se recharge toutes les 1 secondes">
  </div>
<div id=TabCommandesText style="position:absolute;left:12.5%;top:45%">
  Liste Commandes en attente
</div>
<div id=TabCommandes style="position:absolute;left:17.5%;top:48%">
  
</div>
</div>

</div>
</body>
</html>
