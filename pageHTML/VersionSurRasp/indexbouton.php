<!DOCTYPE html>
<html>

    <head>
<meta name="viewport" content="width=content-width">
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
   content: "Version mobile du site";
   display: block;
   color: #777;
   text-align: center;
   font-style: italic;
 }
}
</style>



        <title>jQuery Knob demo</title>
        <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.9.0/jquery.min.js"></script>
        <!--[if IE]><script type="text/javascript" src="excanvas.js"></script><![endif]-->

        <script src="js/jquery.knob.js"></script>
        <script>
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
        </script>
        <style>
            body{
              padding: 0;
              margin: 0px 50px;
              font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
              font-weight: 300;
              text-rendering: optimizelegibility;
            }
            p{font-size: 30px; line-height: 30px}
            div.demo{text-align: center; width: 280px; float: left}
            div.demo > p{font-size: 20px}
        </style>
    </head>
    <body>
    <!-- <div style="width:100%;font-size:40px;letter-spacing:-8px;line-height:40px;">
            <h1>jQuery Knob</h1>
        </div>
        <div>
            <p>Nice, downward compatible, touchable, jQuery dial. <a href="http://flattr.com/thing/674900/jQuery-Knob" target="_blank"><img src="http://api.flattr.com/button/flattr-badge-large.png" alt="Flattr this" title="Flattr this" border="0" /></a></p>
            <p style="font-size: 20px">* implemented interactions : mouse click and wheel mouse, keyboard (on focus) and fingers (touch events)</p>
        </div> 
        <div class="demo">
            <p>Test</p>
            <pre>
            </pre>
            <input class="knob" name="essai" data-step="5" data-fgColor="#66EE66" data-max="360" data-displayInput=true value="0" >
        </div>
<SCRIPT LANGUAGE="Javascript">
var test=$("input.knob").val();
document.write(test);
</SCRIPT>


        <div class="demo">
            <p>&#215; 'cursor' mode</p>
            <pre>
data-width="150"
data-cursor=true
data-thickness=.3
data-fgColor="#222222"
            </pre>
            <input class="knob" data-width="150" data-cursor=true data-fgColor="#222222" data-thickness=.3 value="29">
        </div>
        <div class="demo" >
            <p>&#215; Display previous value</p>
            <pre>
data-displayPrevious=true
data-min="-100"
            </pre>
            <input class="knob" data-width="200" data-min="-100" data-displayPrevious=true value="44">
        </div>
        <div style="clear:both"></div>
        <div class="demo">
            <p>&#215; Angle offset</p>
            <pre>
data-angleOffset=90
data-linecap=round
            </pre>
            <input class="knob" data-angleOffset=90 data-linecap=round value="35">
        </div>

        <div class="demo">

            <p>&#215; Angle offset and arc</p>
            <pre>
data-fgColor="#66CC66"
data-angleOffset=-125
data-angleArc=250
data-rotation=anticlockwise
            </pre>
            <input class="knob" data-angleOffset=-125 data-angleArc=250 data-fgColor="#66EE66" data-rotation="clockwise" data-max="150"data-step="5" value="35">
        </div>
        <div class="demo">
<br>
            <input class="knob" data-angleOffset=-125 data-angleArc=250 data-fgColor="#66EE66" data-rotation="clockwise" data-max="150"data-step="5" value="35">
        </div>
  
     <div class="demo" >
            <p>&#215; 5-digit values, step 1000</p>
            <pre>
data-step="1000"
data-min="-15000"
data-max="15000"
data-displayPrevious=true
            </pre>
            <input class="knob" data-min="-15000" data-displayPrevious=true data-max="15000" data-step="1000" value="-11000">
        </div>
        <div style="clear:both"></div>
        <div style="text-align: center">
            <p style="font-size: 20px">&#215; Overloaded 'draw' method</p>
        </div>
        <div style="background-color: #222; height: 340px">
            <div class="demo" style="background-color:#222; color:#FFF;">
                <pre>
    data-width="75"
    data-fgColor="#ffec03"
    data-skin="tron"
    data-thickness=".2"
    data-displayPrevious=true
                </pre>
                <input class="knob" data-width="75" data-displayPrevious=true data-fgColor="#ffec03" data-skin="tron" data-cursor=true value="75" data-thickness=".2">
            </div>
            <div class="demo" style="background-color:#222; color:#FFF;">
                <pre>
    data-width="150"
    data-fgColor="#ffec03"
    data-skin="tron"
    data-thickness=".2"
    data-displayPrevious=true
                </pre>
                <input class="knob" data-width="150" data-displayPrevious=true data-fgColor="#ffec03" data-skin="tron" data-thickness=".2" value="75">
            </div>
            <div class="demo" style="background-color:#222; color:#FFF;">
                <pre>
    data-width="150"
    data-fgColor="#C0ffff"
    data-skin="tron"
    data-thickness=".1"
    data-angleOffset="180"
                </pre>
                <input class="knob" data-width="150" data-angleOffset="180" data-fgColor="#C0ffff" data-skin="tron" data-thickness=".1" value="35">
            </div>
        </div>
        <div style="clear:both"></div>
        <div class="demo" style="width:100%">
            <p>&#215; Responsive</p>
            <pre>
data-width="80%"
            </pre>
            <div style="width: 30%; border: 3px dashed; margin-bottom: 20px">
                <i>
                    Current div width is 30% of window width.<br>
                    Knob width is 80% of current div.<br>
                    Knob width is 80% of 30% of window width.<br>
                    Test resizing window.
                </i>
                <br>
                <br>
                <input class="knob" data-width="80%" value="35">
            </div>
        </div>
        <div style="clear:both"></div>
        <script>
        function clock() {
            var $s = $(".second"),
                $m = $(".minute"),
                $h = $(".hour");
                d = new Date(),
                s = d.getSeconds(),
                m = d.getMinutes(),
                h = d.getHours();
            $s.val(s).trigger("change");
            $m.val(m).trigger("change");
            $h.val(h).trigger("change");
            setTimeout("clock()", 1000);
        }
        clock();
        </script>
        <div class="demo" style="color:#EEE;background:#222;height:420px;width:100%">
-->
           
            <div style="position:relative;width:350px;margin:auto">
                <div style="position:absolute;left:-200px;top:0px">
                    <input class="knob" data-min="0" data-max="360" data-angleOffset="-90" data-step="5" data-angleArc="180" data-fgColor="#ffec03" data-displayInput=true data-width="300" data-height="300" data-thickness=".3">
                </div>
                <div style="position:absolute;left:110px;top:0px">
                    <input class="knob2" data-min="0" data-max="150" data-step="5" data-angleOffset=-90 data-angleArc=180 data-displayInput=true data-width="300" data-height="300" data-thickness=".3" data-linecap="round">
                </div>
<br><br><br><br><br>
<br><br><br><br><br>
 <div style="position:relative;left:75px;top:0px">
<input type="button" value="Envoi" onClick="AfficherValeur()">
</div>
<SCRIPT LANGUAGE="Javascript">
var test=0;
var test2=0;
function AfficherValeur()
{
test=$("input.knob").val();
test2=$("input.knob2").val();
alert(test+"      "+test2);
}

</SCRIPT>

                            </div>

        </div>

<!--
        <div style="clear:both"></div>
        <div class="demo">
            <p>&#215; Readonly</p>
            <pre>
readonly (or data-readOnly=true)
data-thickness=".4"
data-fgColor="chartreuse"
            </pre>
            <input class="knob" data-fgColor="chartreuse" data-thickness=".4" readonly value="22">
        </div>
        <div class="demo">
            <p>&#215; Dynamic</p>
            <pre>
data-width="200"
            </pre>
            <input type="button" onclick="$('.knob-dyn').knob();" value="knobify!">
            <input type="text" class="knob-dyn" data-width="200" data-cursor=true value="56">
            <pre>
data-width="50"
data-cursor=true
            </pre>
            <input type="button" onclick="$('.knob-dyn2').knob();" value="knobify!">
            <input type="text" class="knob-dyn2" data-width="50" data-thickness=".4" value="56">
        </div>
        <div class="demo" style="height:440px;width:300px">
            <p>&#215; Infinite || iPod click wheel</p>
            <div style="float:left;width:180px;height:320px;padding:20px;background-color:#EEEEEE;text-align:center;">
                <pre>
data-width="150"
data-cursor=true
data-thickness=".5"
data-fgColor="#AAAAAA"
data-bgColor="#FFFFFF"
data-displayInput="false"
+ some code
                </pre>
                <input class="infinite" value="0" data-width="150" data-thickness=".5" data-fgColor="#AAAAAA" data-bgColor="#FFFFFF" data-displayInput="false" data-cursor=true>
            </div>
            <div style="float:left;margin-top:200px;">
                <div class="ival" style="width:80px;text-align:center;font-size:50px;color:#AAA">0</div>
                <div class="idir" style="width:80px;text-align:center;font-size:50px;"></div>
            </div>
        </div>
        <div style="clear:both"></div>
        <div style="margin-top:30px;text-align:center">
            <img src="https://raw.github.com/aterrien/jQuery-Knob/master/secretplan.jpg">
            <p style="font-size:20px;">jQuery Knob is &copy; 2012 Anthony Terrien - MIT License</p> -->
        </div>
    </body>
</html>
