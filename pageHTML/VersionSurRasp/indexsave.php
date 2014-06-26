<html>

<head>


<script Language="Javascript">
var cpt;
var cpt2;
var precedent;
var DistanceDegres;
var fonctionenvoiDistance;
var hexa1,hexa2;
function appelTic1()
{
document.location="cgi-bin/TransfertTic1.cgi";
}
function appelTic0()
{
document.location="cgi-bin/TransfertTic0.cgi";
}
function envoiValeur()
{
//	var valeurcm=parseInt(document.getElementById("distancesaisie").value);
//	var valeurcm=parseInt(document.getElementById("degressaisis").value);
//	hexa1=parseInt(valeurcm/16);
//	hexa2=valeurcm-(hexa1*16);
	//alert(hexa1+"   );
if (cpt==0)
{
if(DistanceDegres==0)
{
var valeurcm=parseInt(document.getElementById("distancesaisie").value);
}
if(DistanceDegres==1)
{
var valeurcm=parseInt(document.getElementById("degressaisis").value);
}
hexa1=parseInt(valeurcm/16);
hexa2=valeurcm-(hexa1*16);

document.location="cgi-bin/FirstHexa.cgi";
cpt++;
}
else
{
	if (cpt<=hexa1)
        {
               	if (precedent==0)
                {
			document.location="cgi-bin/TransfertTic1.cgi";
                       	precedent=1;
                }
                else
                {
                       	document.location="cgi-bin/TransfertTic0.cgi";
                       	precedent=0;
                }

		cpt++;
        }
	else
	{
		if (cpt2==0)
		{
		document.location="cgi-bin/SecHexa.cgi";
		cpt2++;
		}
		else
		{
			 if (cpt2<=hexa2)
                	{
                       		if (precedent==0)
                       		{
                  	       		document.location="cgi-bin/TransfertTic1.cgi";
                        		precedent=1;
                       		}
                       		else
                       		{
                   	       	document.location="cgi-bin/TransfertTic0.cgi";
                       	       	precedent=0;
                       		}
				cpt2++;
               		}
			else
			{
			clearInterval(fonctionenvoiValeur);
			alert(distancecm);
			}
		}
	}
}
}
function TransfertDistance()
{
	DistanceDegres=0;
	//document.location="cgi-bin/TransfertTic0.cgi";
	document.location="cgi-bin/TransfertDistance.cgi";
	precedent=0;
	cpt=0;
	cpt2=0;
	 fonctionenvoiValeur=setInterval(function(){envoiValeur()},150);

}
function TransfertDegres()
{
	 DistanceDegres=1;
        //document.location="cgi-bin/TransfertTic0.cgi";
        document.location="cgi-bin/TransfertDegres.cgi";
        precedent=0;
        cpt=0;
        cpt2=0;
         fonctionenvoiValeur=setInterval(function(){envoiValeur()},150);

}

function set0()
{
    document.location="cgi-bin/set0.cgi";
}
function set1()
{
    document.location="cgi-bin/set1.cgi";
}
function set01()
{
    document.location="cgi-bin/set01.cgi";
}
function clear01(event)
{
    document.location="cgi-bin/clear01.cgi";
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
<img src="page/forward.jpg" id="f" onmousedown="set01()">
<br>
    <img src="page/left.jpg" id="l" onmousedown="set0()">
    <img src="page/right.jpg" id="r" onmousedown="set1()">
<br>
    <img src="page/stop.jpg" id="s" onmousedown="clear01(event)">
    
</div>

</body>
</html>

