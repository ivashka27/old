# Generated by Django 2.0.7 on 2018-11-18 08:53

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('main', '0016_auto_20181113_1848'),
    ]

    operations = [
        migrations.AddField(
            model_name='user',
            name='dislikes',
            field=models.IntegerField(default=0),
        ),
        migrations.AddField(
            model_name='user',
            name='likes',
            field=models.IntegerField(default=0),
        ),
    ]
