<html>

<head>
<meta name="viewport" content="width=content-width">
<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.9.0/jquery.min.js"></script>


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
<!--


<script Language="Javascript">
var delay=1 // ici 1 secondes
var img="image"; // ici nom de l'image a recharger
var src="page/test.jpg"
// fonction � appeler dans le onload de BODY
function RefreshIMG() {
 document.images[img].src=src+"?a="+Math.random(1);
  setTimeout("RefreshIMG()",delay*1000);
}
function TransfertDistance()
{
	var valeurcm=parseInt(document.getElementById("distancesaisie").value);
	valeurcm=str_pad(valeurcm,3,0,'STR_PAD_LEFT');
	document.location="cgi-bin/TransfertDistance.py?distancecm="+valeurcm;
}
function TransfertDegres()
{
	var valeurcm=parseInt(document.getElementById("degressaisis").value);
	valeurcm=str_pad(valeurcm,3,0,'STR_PAD_LEFT');
	document.location="cgi-bin/TransfertDegres.py?degres="+valeurcm;

}


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
function Avancer()
{
  document.location="cgi-bin/Avancer.py";
}
function TournerG()
{
    document.location="cgi-bin/TournerG.py";
}
function TournerD()
{
    document.location="cgi-bin/TournerD.py";
}
function Stop()
{
    document.location="cgi-bin/Stop.py";
}
function Reculer()
{
document.location="cgi-bin/Reculer.py";
}
function ActiverCam()
{
document.location="cgi-bin/ActiverCam.py";
}

</script>
</head>
-->
<body onLoad="RefreshIMG()">
    <div style="text-align:center">
    <h1>Tcomp Commander</h1>
<br>
<div style="position:relative;width:350px;margin:auto">
<div style="position:absolute;left:-200px;top:0px">
<input class="knob" data-min="0" data-max="360" data-angleOffset="-90" data-step="5" data-angleArc="180" data-fgColor="#ffec03" data-displayInput=$
                </div>
                <div style="position:absolute;left:110px;top:0px">
                    <input class="knob2" data-min="0" data-max="150" data-step="5" data-angleOffset=-90 data-angleArc=180 data-displayInput=true data-width="300" data$
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
<form name="form1" method="post" action=""> 
Distance: <input type =text name="distance" id="distancesaisie" size=5 maxlength=5 style="width:200;height:40;"> cm 
<img src="page/ok.jpg" height="64"  width="64" id="o" onmousedown="TransfertDistance()">
<br>
Degres: <input type =text name="degres" id="degressaisis" size=5 maxlength=5 style="width:200;height:40;"> degres
<img src="page/ok.jpg" height="64"  width="64" id="o2" onmousedown="TransfertDegres()">
<br>
</form>
<br>
<img src="page/forward.jpg" id="f" onmousedown="Avancer()">
<br>
    <img src="page/left.jpg" id="l" onmousedown="TournerG()">
   <img src="page/stop.jpg" id="s" onmousedown="Stop()">
   <img src="page/right.jpg" id="r" onmousedown="TournerD()">
<br>
    <img src="page/reculer.jpg" id="re" onmousedown="Reculer()">
<br>
 <img src="page/boutoncam.png" id="bc" onmousedown="ActiverCam()">
<br>
<IMG id="image" name="image" src="page/test.jpg" width=256 height=256 alt="Cette image se recharge toutes les 1 secondes">
-->
</div>

</body>
</html>

