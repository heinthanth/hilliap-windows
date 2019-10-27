<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>It's Work - Hilliap</title>

    <link rel="stylesheet" href="css/style.css">

</head>
<body>
    
    <div id="valign">
        <div id="center-all">
            <h1 id="itsworked"><?php echo "It's Worked!"; ?></h1>
            <img src="image/hilliap.png" id="main-logo">
            <div id="commands">
                <h3>Run as Administrator to create virtualhost</h3>
                <p>
                    # for VirtualHost without SSL <br>
                    a2vhost --ssl false --domain=example.local --root=C:\path\to\document\root
                    <br><br>
                    # for VirtualHost with SSL <br>
                    a2vhost --ssl true --domain=example.local --root=C:\path\to\document\root
                </p>

            </div>
            <h2 id="foot">Thanks for Downloading -- Hein Thanth</h2>
        </div>
    </div>

</body>
</html>