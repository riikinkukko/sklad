from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('api/data/', views.DataListView.as_view(), name='data_list'),
]