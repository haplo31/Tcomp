<html>

<head>


<script Language="Javascript">
var fonctionalea;
var nbalea;
function ActiverCam()
{
fonctionalea=setInterval(function(){alea()},1000);
}
function alea()
{
nbalea==Math.floor(Math.random());
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
alert("lol")  
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
</script>
</head>
<body>
    <div style="text-align:center">
    <h1>Raspberry Pi GPIO</h1>
<br>
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
 <img src="page/test.jpg"&nbalea id="re"> 
</div>

</body>
</html>

