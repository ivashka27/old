from django.contrib import admin

from main.models import Choice
from main.models import Question
from main.models import User

admin.site.register(Question)
admin.site.register(Choice)
admin.site.register(User)