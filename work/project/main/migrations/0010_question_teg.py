# Generated by Django 2.0.7 on 2018-10-09 14:17

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('main', '0009_question_dislikes'),
    ]

    operations = [
        migrations.AddField(
            model_name='question',
            name='teg',
            field=models.TextField(default=''),
            preserve_default=False,
        ),
    ]